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

#include "../diapergluforth.h"

const UINT64 dg_localsregs[] = { 
  dg_r8, dg_r9, dg_r10, dg_r11, dg_r12, dg_r13, dg_r14, dg_r15, 
  dg_rax, dg_rcx, dg_rdx, dg_rbx, dg_rsp, dg_rbp, dg_rsi, dg_rdi,
  dg_xmm0, dg_xmm1, dg_xmm2, dg_xmm3, dg_xmm4, dg_xmm5, dg_xmm6, dg_xmm7,
  dg_xmm8, dg_xmm9, dg_xmm10, dg_xmm11, dg_xmm12, dg_xmm13, dg_xmm14, dg_xmm15  
};


const UINT64 dg_paramintregs[] = {
    dg_rdi,
    dg_rsi,
    dg_rdx,
    dg_rcx,
    dg_r8,
    dg_r9
};

const UINT64 dg_paramfloatregs[] = {
    dg_xmm0,
    dg_xmm1,
    dg_xmm2,
    dg_xmm3,
    dg_xmm4,
    dg_xmm5,
    dg_xmm6,
    dg_xmm7
};

const UINT64 dg_paramintregslocalsindex[] = {
    dg_localsrdiindex,
    dg_localsrsiindex,
    dg_localsrdxindex,
    dg_localsrcxindex,
    dg_localsr8index,
    dg_localsr9index
};

const UINT64 dg_paramfloatregslocalsindex[] = {
    dg_localsxmm0index,
    dg_localsxmm1index,
    dg_localsxmm2index,
    dg_localsxmm3index,
    dg_localsxmm4index,
    dg_localsxmm5index,
    dg_localsxmm6index,
    dg_localsxmm7index
};

// Registers rbp, rbx, r12, r13, r14, and r15 must be preserved.

const unsigned char dg_localsintregallocationorder[] = {
    dg_localsr11index,
    dg_localsr10index,
    dg_localsr9index,
    dg_localsr8index,
    dg_localsrcxindex,
    dg_localsrdxindex,
    dg_localsrsiindex,
    dg_localsrdiindex,
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

UINT64 intparameterslookuptable[6] = 
{
    dg_rdi,
    dg_rsi,
    dg_rdx,
    dg_rcx,
    dg_r8,
    dg_r9
};

UINT64 floatparameterslookuptable[8] = 
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

UINT64 intreturnparameterstable[2] =
{
    dg_rax,
    dg_rdx
};

UINT64 floatreturnparameterstable[2] = 
{
    dg_xmm0,
    dg_xmm1
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
    unsigned char pbuf[24] = "\x55\x48\x8B\xEC\x9C\x9C\x48\x81\x65\xF0\xFF\xFF\xFB\xFF\x9D\x57\xFF\x37\x57\x48\x89\x65\xE0";
    // unsigned char pbuf[14] =    "\x55\x48\x8B\xEC\x9C\x57\xFF\x37\x57\x48\x89\x65\xE0";
    // unsigned char pbuf[6] = "\x55\x48\x8B\xEC\x9C";

    UINT64 currentcompilebufferid;
    UINT64 currentcompilebufferlength;
    
    // rdi = pBHarrayhead
    
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
    //  pushq rdi            0x57             (0x50+rd)
    // pushq old error count
    //  pushq [rdi]          0xFF 0x37        (0xff /6) (error count) // 00 110 111
    // pushq rdi             0x57             // for end of locals variable
    
    
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



// on mac os x for x86 you need to align the stack to a 16 byte boundary before calling any gcc compiled code or
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
    unsigned char mycode[13]  = "\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x08";
    
    UINT64 length = 8;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (numberofparameters > 6)
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


// on mac os x for x86 you need to align the stack to a 16 byte boundary before calling any gcc compiled code or
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

// this alignment code does not affect any registers except the return stack pointer of course
//  it affects flags at this time
// this aligment code allows for local variable space to be added to the return stack at run time
//  just push to return stack or subtract from esp and then and movl esp -> [ebp -0x30]

const char* dg_compilealignretstackbname = "dg_compilealignretstackb";

void dg_compilealignretstackb(
    Bufferhandle* pBHarrayhead,
    UINT64 numberofintparameters,
    UINT64 numberoffloatparameters)
{
    // movq  [rbp-0x20] -> rsp                0x48 0x8B 0x65 0xE0  // seems rex is needed
    // andq  rsp & 0xfffffffffffffff0 -> rsp  0x48 0x83 0xE4 0xF0
    // subq  rsp - 0x0n -> rsp                0x48 0x83 0xEC 0x00
    unsigned char mycode[13] = "\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x08";
    
    UINT64 length = 8;
    UINT64 numberofparametersonstack = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (numberofintparameters > 6)
    {
        numberofparametersonstack = numberofintparameters - 6;
    }
    
    if (numberoffloatparameters > 8)
    {
        numberofparametersonstack += (numberoffloatparameters - 8);
    }
    
    if ((numberofparametersonstack & 1) == 1)
    {
        length = 12;
    }
    
    dg_compilesegment (
        pBHarrayhead,
        (const char*)mycode,
        length);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compilealignretstackbname);
    }
}


const char dg_forthshadowcommaname[] = "SHADOW,";

void dg_forthshadowcomma (Bufferhandle* pBHarrayhead)
{
    // mac doesn't have shadow parameters... needed be able to use
    //   common routines for compilation
}






const char* dg_compilentoparametername = "dg_compilentoparameter";

void dg_compilentoparameter (
    Bufferhandle* pBHarrayhead,
    UINT64 n,
    UINT64 parameter) // 0 based, 0 = first parameter
{
    UINT64 regparametertable[6] =
    {
        dg_rdi,
        dg_rsi,
        dg_rdx,
        dg_rcx,
        dg_r8,
        dg_r9
    };
    
    if (parameter < 6)
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
    
    dg_compilealignretstack(
        pBHarrayhead,
        7); // want just the and rsp... to get multiple of 16
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }
    
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
    
    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        compilebufid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcompilesafecallbuffername);
        return;
    }
    
    // safe call to forth routine
//  rdi <- pBHarrayhead    0x48 0x8B 0x7D 0xF0
//  push return offset (don't know it yet...)
//  push return bufferid
//  push address of jump buffer (this is where forth routine returns)
//  rdx <- target offset
//  rsi <- target bufferid
//  rax <- &getpbufferoffset
//  jmp rax OR do the RIP [R] JMP, thing

    // push offset
    dg_compilemovntorax ( // "\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        0); // return offset
    
    dg_compilepushregtoret( // "\x50" 2 bytes
        pBHarrayhead,
        dg_rax);
    
    // dg_compilemovregtobracketrbpd8(
    //    pBHarrayhead,
    //    dg_rax,
    //    -0x30); // return offset
    
    // push bufferid
    dg_compilemovntorax ( // "\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        compilebufid); // return bufferid (which is current compile bufferid)
    
    // dg_compilemovregtobracketrbpd8(
    //    pBHarrayhead,
    //    dg_rax,
    //    -0x38); // return bufferid
    
    dg_compilepushregtoret( // "\x50" 2 bytes
        pBHarrayhead,
        dg_rax);// push pBHarrayhead + sizeof(Bufferhandle) .. this is the return address

    dg_forthshadowcomma(pBHarrayhead);
    
    dg_compilemovbracketrbpd8toreg (
        pBHarrayhead,
        dg_rax,
        -0x10); // -0x10
    
    dg_compileaddn32torax (
        pBHarrayhead,
        sizeof(Bufferhandle));
    
    // dg_compilemovregtobracketrbpd8(
    //    pBHarrayhead,
    //    dg_rax,
    //    -0x40); // return bufferid
    
    dg_compilepushregtoret( // "\x50" 2 bytes
        pBHarrayhead,
        dg_rax);
    
    dg_compilemovntoreg ( // "\x48\xBE\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        pints[1],
        dg_rsi); // target bufferid
    
    dg_compilemovntoreg ( // "\x48\xBA\x00\x00\x00\x00\x00\x00\x00\x00" 10 bytes
        pBHarrayhead,
        pints[0],
        dg_rdx); // target offset
    
    dg_compilemovbracketrbpd8toreg (
        pBHarrayhead,
        dg_rdi,
        -0x10); // pBHarrayhead from frame
    
    dg_compilecalladdress ( // "\xFF\x15\x02\x00\x00\x00\xEB\x08\x00\x00\x00\x00\x00\x00\x00\x00" 16 bytes
        pBHarrayhead,
        (UINT64)&dg_getpbufferoffset); // target address
    
    // dg_compilepushbracketrbpd8 (
    //    pBHarrayhead,
    //    -0x40);
    
    dg_compilemovbracketrbpd8toreg (
        pBHarrayhead,
        dg_rdi,
        -0x10); // pBHarrayhead from frame
    
    dg_compilejumptorax(pBHarrayhead); // "\xFF\xE0" 2 bytes
    
    // dg_compilecalltorax(pBHarrayhead);
    
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

// jump boffer code assumes it is being called from a subroutine that did init locals
void dg_initjumpbuffer (Bufferhandle* pBHarrayhead)
{
    const char* pError;
    
    // popq  rsi                              0x5E // bufferid
    // popq  rdx                              0x5A // offset
    // movq  [rbp-0x10] -> rdi                0x48 0x8B 0x7D 0xF0  // pBHarrayhead
    // movq  [rbp-0x20] -> rsp                0x48 0x8B 0x65 0xE0  // seems rex is needed
    // andq  rsp & 0xfffffffffffffff0 -> rsp  0x48 0x83 0xE4 0xF0
    // subq  rsp - 0x08n -> rsp               0x48 0x83 0xEC 0x08
    // movq  &dg_getpbufferoffset -> rax      0x48 0xB8 0xnn 0xnn 0xnn 0xnn 0xnn 0xnn 0xnn 0xnn
    // call  rax                              0xFF 0xD0
    // jump  rax                              0xFF 0xE0
    
    unsigned char pbuf[33] = "\x5E\x5A\x48\x8B\x7D\xF0\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x08\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xD0\xFF\xE0";
    // unsigned char pbuf[39] = "\x48\x8B\x55\xD0\x48\x8B\x75\xC8\x48\x8B\x7D\xF0\x48\x8B\x65\xE0\x48\x83\xE4\xF0\x48\x83\xEC\x08\x48\xB8\x00\x00\x00\x00\x00\x00\x00\x00\xFF\xD0\xFF\xE0";

    *((UINT64*)(pbuf + 20)) = (UINT64)(&dg_getpbufferoffset);
    
    pError = dg_movebytes(
        pbuf,
        ((unsigned char*)pBHarrayhead) + sizeof(Bufferhandle),
        32);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_movebytesname);
        dg_pusherror(pBHarrayhead, dg_initjumpbuffername);
    }
}


const char* dg_determineparameterregistername = "dg_determineparameterregister";

UINT64 dg_determineparameterregister (
    Bufferhandle* pBHarrayhead,
    UINT64 parameterindex)
{
    UINT64 parameterregister;
    UINT64 numberofintparameters;
    UINT64 numberoffloatparameters;
    UINT64 extraparametersarefloatsflag = FORTH_FALSE;
    UINT64 x;
    UINT64 floatparameterindex;
    UINT64 numberofintparametersonstack = 0;
    // UINT64 numberoffloatparametersonstack = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return((UINT64)-1);
    }
    
    numberofintparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcparameters);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_determineparameterregistername);
        return((UINT64)-1);
    }
    
    numberoffloatparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_determineparameterregistername);
        return((UINT64)-1);
    }
    
    extraparametersarefloatsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_extraparametersfloatsflag);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
         dg_pusherror(pBHarrayhead, dg_determineparameterregistername);
         return((UINT64)-1);
    }
    
    if ( 
         (parameterindex < numberofintparameters) ||
         ( 
           (parameterindex >= (numberofintparameters + numberoffloatparameters)) && 
           (extraparametersarefloatsflag == FORTH_FALSE)
         )
       )
    {
        // it's an integer parameter
        if (parameterindex < (sizeof(intparameterslookuptable)/sizeof(UINT64)))
        {
            // it's in a register
            return(intparameterslookuptable[parameterindex]);
        }
        
        // it's on the stack
        x = parameterindex - (sizeof(intparameterslookuptable)/sizeof(UINT64));
        
        // I doubt this is possible but... you never know... someone inputs a ton of parameters...
        if (x > dg_cparameteronstackflag)
        {
            dg_pusherror(pBHarrayhead, dg_parametersovermaxsizeerror);
            dg_pusherror(pBHarrayhead, dg_determineparameterregistername);
            return((UINT64)-1);
        }
        
        return(x | dg_cparameteronstackflag);
    }
    
    // what's the rule when you have a variable parameter list?
    //  the way it is now, extra parameters are the parsing mode at the end
    
    // it's a float parameter
     
    floatparameterindex = parameterindex - numberofintparameters; 
    
    if (  floatparameterindex < (sizeof(floatparameterslookuptable)/sizeof(UINT64)) )
    {
        // it's in a register
        return(floatparameterslookuptable[floatparameterindex]);
    }
    
    // it's on the stack, if there are any int parameters on the stack, it goes after that...
    if (numberofintparameters > (sizeof(intparameterslookuptable)/sizeof(UINT64)))
    {
        numberofintparametersonstack = numberofintparameters - (sizeof(intparameterslookuptable)/sizeof(UINT64));
    }

    return(((floatparameterindex - (sizeof(floatparameterslookuptable)/sizeof(UINT64))) + numberofintparametersonstack) | dg_cparameteronstackflag);
    
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
                //  the comment below is incorrect... 2023 Mar 31 J.N.
                //  [rbp - 0x28] = local 0  if nothing else on frames (there are 4 things...)
                //  [rbp - 0x30] = local 1 etc

                // parameter type is the index on the frame...
                parametertype = dg_popdatastack(pBHarrayhead);
                
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                psf->displacementsize = 0; // use at least 0  bytes to encode the displacement
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
                
                parametertype = dg_determineparameterregister (
                    pBHarrayhead,
                    parametertype);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                if (dg_cparameteronstackflag == (parametertype & dg_cparameteronstackmask) )
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

                    /// getulowestbits of regspreserved where u is paramreg's localsregsindex + 1
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
                    // psf->size = sizeof(UINT64); // xmm registers may not work if you do this...

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
                
                psf->size = dg_getsizefromreg (psf->basereg);
                
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
                
                parametertype = dg_determineparameterregister (
                    pBHarrayhead,
                    parametertype);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }

                // dg_printzerostring(
                //    pBHarrayhead,
                //    (unsigned char*)" \ncall subs frame parametertype = ");

                // dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)parametertype);
                
                if (dg_cparameteronstackflag == (parametertype & dg_cparameteronstackmask) )
                {
                    // dg_printzerostring(
                    //    pBHarrayhead,
                    //    (unsigned char*)" is on stack ");

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
                    // dg_printzerostring(
                    //    pBHarrayhead,
                    //    (unsigned char*)" is preserved ");

                    // parameter reg was preserved which means it was moved to the return stack
                    
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
                    // dg_printzerostring(
                    //    pBHarrayhead,
                    //    (unsigned char*)" is an xmm reg ");

                    if (psf->memmode == dg_memmodeunknown)
                    {
                        psf->memmode = dg_memmodexmmreg;
                    }
                    
                    psf->size = 16;
                    
                    notdoneflag = FORTH_FALSE;
                    
                    break;
                }

                // dg_printzerostring(
                //        pBHarrayhead,
                //        (unsigned char*)" is a regular reg ");
                
                // promote memmode to defaultreg if not already higher
                if (psf->memmode == dg_memmodeunknown)
                {
                    psf->memmode = dg_memmodedefaultreg;
                }
                
                psf->size = dg_getsizefromreg (psf->basereg);
                
                notdoneflag = FORTH_FALSE;
            
                break;
                
            default:
/*                
                if (dg_cparameteronstacknoframeflag == (parametertype & dg_cparameteronstackmask) )
                {
                    // it's on the stack...
                    // need rstack depth
                    rstackdepth = dg_defaultnoframerstackdepth; 
                        
                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                        return;
                    }   
                     
                    // need to determine if using rbp as base reg or not and adjust
                    psf->displacementsize = 0; // use at least 0  bytes to encode the displacement
                    psf->displacement = ((parametertype & (~dg_cparameteronstackmask)) + rstackdepth) * sizeof(UINT64); 
                        // can't overflow because of mask
                        // + 1 because function return is at 0... assumes stack pointer
                        // going to need to track stack pointer offset and adjust...
                    psf->basereg = dg_rsp;       
                    psf->memmode = dg_memmodemodrslashm;
                    // psf->size = addresssize;  // leaving it on default size so xmm registers work
                    
                    notdoneflag = FORTH_FALSE;
                
                    break;
                }
                
                if (dg_cparameteronstackflag == (parametertype & dg_cparameteronstackmask) )
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
*/                
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


// const char dg_forthparencurlyname[] = "(<";
// const char dg_forthframeparamscurlyname[] = "FRAME-PARAMS<";

void dg_forthframeparamscurly (Bufferhandle* pBHarrayhead)
{
    UINT64 localwordid;
    UINT64 localswordlistid;
    
    UINT64 foundendflag = FORTH_FALSE;

    unsigned char* pname;
    UINT64 namelength = 0;
    
    INT64 compareflag;
    UINT64 parsingfloatsflag = FORTH_FALSE; // start out parsing ints
    
    UINT64 i;
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
            dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
            return;
        }
            
        if (namelength != 0)
        {
            
            pError = dg_comparebytes (
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
                pError = dg_comparebytes (
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
                    //  if we are in float mode push this to the string stack for later
                    //  because on Mac, floating point parameters come after int parameters
                    //  on the stack, regardless of their position in the C prototype
                    if (parsingfloatsflag != FORTH_FALSE)
                    {
                        // we are parsing float paramters
                        dg_pushlstring (
                            pBHarrayhead,
                            DG_STRINGOFFSETSTACK_BUFFERID,
                            DG_STRINGSTRINGSTACK_BUFFERID,
                            namelength,
                            pname);
                            
                        if (dg_geterrorcount(pBHarrayhead) != 0)
                        {
                            dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
                            return;
                        }

                        if (numberoffloatparameters < dg_numberofparamfloatregs)
                        { 
                            myparamregsused = dg_setbit(
                                 myparamregsused, 
                                 dg_paramregsindextolocalsregindex(
                                 numberoffloatparameters, 
                                 1)); // it's a float reg
                        }
                        
                        numberoffloatparameters++;
                    }
                    else
                    {
                        // it's an int parameter
                        // add the symbol name - it's a constant
                        localwordid = dg_createdconstantdef (
                            pBHarrayhead,
                            numberofintparameters, // databufoffset
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

                        if (numberofintparameters < dg_numberofparamintregs)
                        { 
                            myparamregsused = dg_setbit(
                                 myparamregsused, 
                                 dg_paramregsindextolocalsregindex(
                                 numberofintparameters, 
                                 0)); // it's an int reg
                        }
                        
                        numberofintparameters++;
                    }
                }
            }
        }
    }

    // time to do the floating point parameters that are on the string stack
    
    // for each parameter name on the string stack:
    //  get a pointer to and length of the string staring with the deepest string
    //  create a constant definition and link it into the locals wordlist
    //    the parameter index is numberofintparameters plus which float this is
    //  that's it
    if (numberoffloatparameters != 0)
    {
        stringstackdepth = dg_getnumberoflstringsonstack(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID);
      
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
            return;
        }
        
        for (i = 0; i < numberoffloatparameters; i++)
        {
            pname = dg_getplstring(
                pBHarrayhead,
                DG_STRINGOFFSETSTACK_BUFFERID,
                DG_STRINGSTRINGSTACK_BUFFERID,
                stringstackdepth - (numberoffloatparameters - i),  // stringid,
                &namelength);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
                return;
            }
                
            // add the symbol name - it's a dconstant, paramindex dg_isparamusingframe
            localwordid = dg_createdconstantdef (
                pBHarrayhead,
                numberofintparameters + i, // databufoffset
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
        }
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_extraparametersfloatsflag,
        parsingfloatsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthframeparamscurlyname);
        return;
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


// const char dg_forthnoframeparamscurlyname[] = "NO-FRAME-PARAMS<";

void dg_forthnoframeparamscurly (Bufferhandle* pBHarrayhead)
{
    UINT64 localwordid;
    UINT64 localswordlistid;
    
    UINT64 foundendflag = FORTH_FALSE;

    unsigned char* pname;
    UINT64 namelength = 0;
    
    INT64 compareflag;
    UINT64 parsingfloatsflag = FORTH_FALSE; // start out parsing ints
    
    UINT64 i;
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
            dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
            return;
        }
            
        if (namelength != 0)
        {
            
            pError = dg_comparebytes (
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
                pError = dg_comparebytes (
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
                    //  if we are in float mode push this to the string stack for later
                    //  because on Mac, floating point parameters come after int parameters
                    //  on the stack, regardless of their position in the C prototype
                    if (parsingfloatsflag != FORTH_FALSE)
                    {
                        // we are parsing float paramters
                        dg_pushlstring (
                            pBHarrayhead,
                            DG_STRINGOFFSETSTACK_BUFFERID,
                            DG_STRINGSTRINGSTACK_BUFFERID,
                            namelength,
                            pname);
                            
                        if (dg_geterrorcount(pBHarrayhead) != 0)
                        {
                            dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
                            return;
                        }

                        if (numberoffloatparameters < dg_numberofparamfloatregs)
                        { 
                            myparamregsused = dg_setbit(
                                 myparamregsused, 
                                 dg_paramregsindextolocalsregindex(
                                 numberoffloatparameters, 
                                 1)); // it's a float reg
                        }
                        
                        numberoffloatparameters++;
                    }
                    else
                    {
                        // it's an int parameter
                        // add the symbol name - it's a constant
                        localwordid = dg_createdconstantdef (
                            pBHarrayhead,
                            numberofintparameters, // databufoffset
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

                        if (numberofintparameters < dg_numberofparamintregs)
                        { 
                            myparamregsused = dg_setbit(
                                 myparamregsused, 
                                 dg_paramregsindextolocalsregindex(
                                 numberofintparameters, 
                                 0)); // it's an int reg
                        }
                        
                        numberofintparameters++;
                    }
                }
            }
        }
    }

    // time to do the floating point parameters that are on the string stack
    
    // for each parameter name on the string stack:
    //  get a pointer to and length of the string staring with the deepest string
    //  create a constant definition and link it into the locals wordlist
    //    the parameter index is numberofintparameters plus which float this is
    //  that's it
    if (numberoffloatparameters != 0)
    {
        stringstackdepth = dg_getnumberoflstringsonstack(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID);
      
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
            return;
        }
        
        for (i = 0; i < numberoffloatparameters; i++)
        {
            pname = dg_getplstring(
                pBHarrayhead,
                DG_STRINGOFFSETSTACK_BUFFERID,
                DG_STRINGSTRINGSTACK_BUFFERID,
                stringstackdepth - (numberoffloatparameters - i),  // stringid,
                &namelength);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
                return;
            }
                
            // add the symbol name - it's a dconstant, paramindex dg_isparamusingframe
            localwordid = dg_createdconstantdef (
                pBHarrayhead,
                numberofintparameters + i, // databufoffset
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
        }
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_extraparametersfloatsflag,
        parsingfloatsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnoframeparamscurlyname);
        return;
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


// const char dg_forthimpname[] = "IMP";

void dg_forthimp(Bufferhandle* pBHarrayhead)
{
    dg_pushdatastack(pBHarrayhead, dg_rip);
    dg_pushdatastack(pBHarrayhead, 0);  // displacement 
    dg_pushdatastack(pBHarrayhead, 4);  // displacement size  
    dg_pushdatastack(pBHarrayhead, dg_isbasedisplacement); 
}


const char* dg_compileosymbolimportstuffname = "dg_compileosymbolimportstuff";

// on windows you need to branch over where the import link will go
//  the displacement of the previous instruction should already be set with the IMP command...
// on Mac you don't need to do anything... and the displacement for IMP has to be 0
//  since the Mac linker adds to the compiled offset instead of just setting it
UINT64 dg_compileosymbolimportstuff(Bufferhandle* pBHarrayhead)
{
    UINT64 ccbufid;
    UINT64 ccbuflength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)-1);
    }

    ccbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compileosymbolimportstuffname);
    }

    ccbuflength = dg_getbufferlength(
        pBHarrayhead,
        ccbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_compileosymbolimportstuffname);
    }
    
    return(ccbuflength - sizeof(UINT32));
}


const char* dg_compilecodelinkname = "dg_compilecodelink";

UINT64 dg_compilecodelink(Bufferhandle* pBHarrayhead)
{
    UINT64 x = 0;
    UINT64 ccbufid;
    UINT64 ccbuflength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)-1);
    }

    // on mac you do this:
    dg_compilejmpbracketoffset(
        pBHarrayhead,
        0); // this is the link on Mac... 
            // has to be 0 because the mac linker adds the offset to the true link

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

    return(ccbuflength - sizeof(UINT32));  // the size of the displacement
}


const char* dg_subparamsnotbalanced = " - parameters not balanced. If before function call, need one >IPARAM or >FPARAM after each parameter. If after function call, need one IPARAM> or FPARAM> before each parameter.";

// const char dg_forthendsubparamscommaname[] = ")),";

void dg_forthendsubparamscomma(Bufferhandle* pBHarrayhead)
{
    UINT64 numberofintparameters;
    UINT64 numberoffloatparameters;
    UINT64 numberofintparametersonstack;
    UINT64 numberoffloatparametersonstack;
    
    UINT64 i = 0;
    UINT64 x;
 
    UINT64 whichintparameter;
    UINT64 whichfloatparameter;   
    
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
    
    whichintparameter = numberofintparameters;
    
    numberoffloatparameters = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_callsubnumberoffloats);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }
    
    whichfloatparameter = numberoffloatparameters;
    
    dg_compilealignretstackb(
        pBHarrayhead,
        numberofintparameters,
        numberoffloatparameters);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
        return;
    }
    
    numberofintparametersonstack = 0;
                
    if 
    (
        numberofintparameters > ( sizeof(intparameterslookuptable) / sizeof(UINT64) ) 
    )
    {
        numberofintparametersonstack = 
            (numberofintparameters - (sizeof(intparameterslookuptable)/sizeof(UINT64)));
    }
    
    numberoffloatparametersonstack = 0;
    
    if 
    (
        numberoffloatparameters > ( sizeof(floatparameterslookuptable) / sizeof(UINT64) ) 
    )
    {
        numberoffloatparametersonstack = 
            (numberoffloatparameters - (sizeof(floatparameterslookuptable)/sizeof(UINT64)));
    }
    
    // compile room for parameters on stack
    i = numberofintparametersonstack + numberoffloatparametersonstack;
    
    if (i != 0)
    {
        if (i > (largestsignedint / sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_invalidparametererror);
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
            return;
        }
    
        dg_compilesubnfromrsp(
            pBHarrayhead,
            i * sizeof(UINT64));
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
            return;
        }
    }
    
    i = numberofintparameters + numberoffloatparameters;
    
    while (i > 0)
    {
        // data stack doesn't move, but BHarray does... so the length pointer
        //  might become invalid
        x = dg_popdatastack(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
            return;
        }
    
        // the top number on the stack should be one of >IPARAM >FPARAM IPARAM> FPARAM>
        switch(x)
        {
            // dg_printzerostring(pBHarrayhead, (unsigned char*)"x = ");
            // dg_writestdoutuint64tohex(pBHarrayhead, x);
            // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
            
            case dg_istointsubparam:
            
                if (0 == whichintparameter)
                {
                    dg_pusherror(pBHarrayhead, dg_invalidparametererror);
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                // predecrement
                whichintparameter--;
                
                // dg_printzerostring(pBHarrayhead, (unsigned char*)"which int = ");
                // dg_writestdoutuint64tohex(pBHarrayhead, whichintparameter);
                // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
                
                if (whichintparameter < (sizeof(intparameterslookuptable)/sizeof(UINT64)))
                {
                    // it's an int register
                    dg_pushdatastack(
                        pBHarrayhead,
                        intparameterslookuptable[whichintparameter]);
                        
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
                        (whichintparameter - (sizeof(intparameterslookuptable)/sizeof(UINT64))) * sizeof(UINT64));
                        
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
                    
                    dg_forthmovcomma(pBHarrayhead);
                    
                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }
                
                break;
                
            case dg_isptointsubparam:
            
                if (0 == whichintparameter)
                {
                    dg_pusherror(pBHarrayhead, dg_invalidparametererror);
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                // predecrement
                whichintparameter--;
                
                // dg_printzerostring(pBHarrayhead, (unsigned char*)"which int = ");
                // dg_writestdoutuint64tohex(pBHarrayhead, whichintparameter);
                // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
                
                if (whichintparameter < (sizeof(intparameterslookuptable)/sizeof(UINT64)))
                {
                    // it's an int register
                    dg_pushdatastack(
                        pBHarrayhead,
                        intparameterslookuptable[whichintparameter]);
                        
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
                        (whichintparameter - (sizeof(intparameterslookuptable)/sizeof(UINT64))) * sizeof(UINT64));
                        
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
                    
                    dg_forthleacomma(pBHarrayhead);
                    
                    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                        return;
                    }
                }
                
                break;
                
            case dg_istofloatsubparam:
                
                if (0 == whichfloatparameter)
                {
                    dg_pusherror(pBHarrayhead, dg_invalidparametererror);
                    dg_pusherror(pBHarrayhead, dg_pulloneaddressingmodename);
                    return;
                }
                
                // predecrement
                whichfloatparameter--;
                
                if (whichfloatparameter < (sizeof(floatparameterslookuptable)/sizeof(UINT64)))
                {
                    // dg_printzerostring(pBHarrayhead, (unsigned char*)"which float = ");
                    // dg_writestdoutuint64tohex(pBHarrayhead, whichfloatparameter);
                    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
                    
                    // dg_printzerostring(pBHarrayhead, (unsigned char*)"reg = ");
                    // dg_writestdoutuint64tohex(pBHarrayhead, floatparameterslookuptable[whichfloatparameter]);
                    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
                
                    dg_pushdatastack(
                        pBHarrayhead,
                        floatparameterslookuptable[whichfloatparameter]);
                    
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
                        ( sizeof(UINT64) *
                            (
                                numberofintparametersonstack +
                                ( whichfloatparameter  - (sizeof(floatparameterslookuptable)/sizeof(UINT64)) )
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
                
                if (0 == whichintparameter)
                {
                    dg_pusherror(pBHarrayhead, dg_invalidparametererror);
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
                
                // predecrement
                whichintparameter--;
                
                if (whichintparameter < (sizeof(intreturnparameterstable)/sizeof(UINT64)))
                {
                    // it's an int register
                    dg_pushdatastack(
                        pBHarrayhead,
                        intreturnparameterstable[whichintparameter]);
                        
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
                    dg_pusherror(pBHarrayhead, (const char*)"too many integer return parameters (only two are allowed)");
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
                
                break;
                
            case dg_isfromfloatsubparam:
            
                if (0 == whichfloatparameter)
                {
                    dg_pusherror(pBHarrayhead, dg_invalidparametererror);
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                }
                
                // predecrement
                whichfloatparameter--;
                
                if (whichfloatparameter < (sizeof(floatparameterslookuptable)/sizeof(UINT64)))
                {
                    dg_pushdatastack(
                        pBHarrayhead,
                        floatparameterslookuptable[whichfloatparameter]);
                    
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
                    dg_pusherror(pBHarrayhead, (const char*)"too many float return parameters (only two are allowed... but I'm allowing eight)");
                    dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                    return;
                }
                
                break;
                
            default:
            
                dg_pusherror(pBHarrayhead, (const char*)" - expected an >IPARAM or >FPARAM or IPARAM> or FPARAM> marker on top of the data stack for each parameter. Anything else is an error.");
                dg_pusherror(pBHarrayhead, dg_forthendsubparamscommaname);
                
                break;
        }
        
        i--;
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


void dg_forthoimportcodelink(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, DG_IMPORT_LINK_IMPORT_OFFSET);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_isoimportcodelinkname);
        return;
    }
    
    dg_forthminus(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_isoimportcodelinkname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, dg_isccbufferoffsetnobracket);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_isoimportcodelinkname);
        return;
    }
}

