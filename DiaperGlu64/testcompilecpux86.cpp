// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2021 James Patrick Norris
//
//    This file is part of DiaperGlu v5.0.
//
//    DiaperGlu v5.0 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.0 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.0; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// January 9, 2021            //
// version 5.0                //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"

void testdg_compilemovregtoreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(UINT64, UINT64);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtoreg\n");

    // mov rcx->rax success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64, UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x20, 0x30);

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax rdx->r8->rax success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax rdx->r8->rax success case  - error compiling test routine\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param2reg,
        dg_r8);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax rdx->r8->rax success case  - error compiling test routine\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax rdx->r8->rax success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64, UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax rdx->r8->rax success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x30, 0x20);

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtoreg rcx->rax rdx->r8->rax success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }



    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilenegatereg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(UINT64);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilenegatereg\n");

    // negate rax=-0x20 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rax=-0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rax=-0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_rax);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rax=-0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rax=-0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0xFFFFFFFFFFFFFFE0);

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rax=-0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rcx=-0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilenegatereg(
        &BHarrayhead,
        dg_param1reg);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rcx=-0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rcx=-0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0xFFFFFFFFFFFFFFE0);

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg rcx=-0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg r8=-0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_r8);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_r8);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg r8=-0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg r8=-0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0xFFFFFFFFFFFFFFE0);

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilenegatereg r8=-0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compileaddregtoreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(UINT64, UINT64);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileaddregtoreg\n");

    // add rcx=0x20 r8=3 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=-0x20 r8=0x3 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=-0x20 rdx=0x3 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_param2reg);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param2reg,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=-0x20 rdx=0x3 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64, UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=-0x20 rdx=0x3 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x20, 0x03);

    if (x != 0x23)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=-0x20 rdx=0x3 success case - return not 0x23, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg r8=0x0304050613141516 rax=0x2030405021314151 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param2reg,
        dg_r8);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg r8=0x0304050613141516 rax=0x2030405021314151 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64, UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg r8=0x0304050613141516 rax=0x2030405021314151 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x2030405021314151, 0x0304050613141516);

    if (x !=   0x2334455634455667)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg r8=0x0304050613141516 rax=0x2030405021314151 success case - return not 0x2334455682455667, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg r8=0x0304050613141516 rax=0x2030405021314151 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param2reg,
        dg_r8);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_r8);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=0x2030405021314151 r8=0x0304050613141516 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64, UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=0x2030405021314151 r8=0x0304050613141516 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x2030405021314151, 0x0304050613141516);

    if (x != 0x2334455634455667)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddregtoreg rcx=0x2030405021314151 r8=0x0304050613141516 success case - return not 0x2334455682455667, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilesubn8fromrsp()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64 (*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_subn8fromrsp\n");

    // subtract 0x20 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp 0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp 0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x20);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rsp);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_rax);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp 0x20 success case  - error compiling test routine\n");
        return;
    }
    
    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp 0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp subtract 0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp -0x10 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        -0x10);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rsp);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_rax);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp -0x10 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp -0x10 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_subn8fromrsp subtract -0x10 success case - return not 0x10, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compileaddn8torsp()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileaddn8torsp\n");

    // add 0x20 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp 0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp 0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rcx);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rsp);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_rax);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp 0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp 0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x08)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp subtract 0x20 success case - return not 0x08, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp -0x10 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compileaddn8torsp(
        &BHarrayhead,
        -0x10);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rsp);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_rax);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp -0x10 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp -0x10 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddn8torsp subtract -0x10 success case - return not 0x10, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilepushntoret()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilepushntoret\n");

    // push 0x20 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret 0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret 0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushntoret(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret 0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret 0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret 0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret -0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushntoret(
        &BHarrayhead,
        (UINT64)-0x20);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret -0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret -0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != (UINT64)-0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushntoret -0x20 success case - return not -0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilepopregfromret()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilepopregfromret\n");

    //  0x20 pop rax success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret pop rax 0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret pop rax 0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushntoret(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret pop rax 0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret pop rax 0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret pop rax 0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret 0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushntoret(
        &BHarrayhead,
        (UINT64)-0x20);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_r8);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret -0x20 pop r8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret -0x20 pop r8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != (UINT64)-0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret -0x20 pop r8 success case - return not -0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret -0x20 rcx success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushntoret(
        &BHarrayhead,
        (UINT64)-0x20);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rcx);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret -0x20 pop rcx success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret -0x20 pop rcx success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != (UINT64)-0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepopregfromret -0x20 pop rcx success case - return not -0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilepushregtoret()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(UINT64);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilepushregtoret\n");

    //  0x2030405060708090 pop rax success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push rcx 0x2030405060708090 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push rcx 0x2030405060708090 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_param1reg);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push rcx 0x2030405060708090 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push rcx 0x2030405060708090 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x2030405060708090);

    if (x != 0x2030405060708090)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push rcx 0x2030405060708090 success case - return not 0x2030405060708090, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push r8 0x2030405060708090 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_r8);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_r8);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push r8 0x2030405060708090 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push r8 0x2030405060708090 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x2030405060708090);

    if (x != 0x2030405060708090)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepushregtoret push r8 0x2030405060708090 success case - return not 0x2030405060708090, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilecalloffset()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilecalloffset\n");

    //  0x2030405060708090 pop rax success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalloffset 0x08 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalloffset 0x08 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilecalloffset(
        &BHarrayhead,
        0x08);

    dg_compilesegment(
        &BHarrayhead,
        (const char*)"\x21\x22\x23\x24\x25\x26\x27\x28",
        8);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalloffset 0x08 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalloffset 0x08 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)x) != 0x2827262524232221)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalloffset 0x08 success case - return not 0x2827262524232221, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // test negative offset
    // test over range positive offset
    // test over range negative offset

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilejmpoffset()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilejmpoffset\n");

    //  0x2030405060708090 pop rax success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilejmpoffset 0x08 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilejmpoffset 0x08 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilecalloffset(
        &BHarrayhead,
        0x0);

    dg_compilejmpoffset(
        &BHarrayhead,
        0x08);

    dg_compilesegment(
        &BHarrayhead,
        (const char*)"\x21\x22\x23\x24\x25\x26\x27\x28",
        8);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilejmpoffset 0x08 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilejmpoffset 0x08 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(x+5)) != 0x2827262524232221) // this assumes length of compiled jmp is 5 bytes
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilejmpoffset 0x08 success case - return not 0x2827262524232221, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // test negative offset
    // test over range positive offset
    // test over range negative offset

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilecalladdress()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(UINT64);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilecalladdress\n");

    //  0x2030405060708090 pop rax success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalladdress success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalladdress success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilecalladdress(
        &BHarrayhead,
        (UINT64)&dg_bswap);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalladdress success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(UINT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalladdress success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0x2827262524232221);

    if (x != 0x2122232425262728) // this assumes length of compiled jmp is 5 bytes
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecalladdress success case - return not 0x2122232425262728, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_callbuffer()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_callbuffer and whether os lies about allocating executable memory\n");
	
	// success case not requiring alignment
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_callbuffer success case not requiring alignment - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_callbuffer success case not requiring alignment - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compilereturn(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_callbuffer success case not requiring alignment - could not compile ret\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}

UINT64 dg_returntestuint64 ()
{
    return (0x1122998833447766);
}

/*
// moved to assembly language file for windows compatibility
UINT128 dg_returntestuint128 ()
{    
    return (-5);
}
*/

UINT64 dg_returnparam0plus1 (UINT64 x)
{
    return (x+1);
}

UINT64 dg_returnparam0plusparam1 (UINT64 x1, UINT64 x2)
{
    return (x1 + x2);
}

UINT64 dg_returnp0plusp1plusp2 (UINT64 x1, UINT64 x2, UINT64 x3)
{
    return (x1 + x2 + x3);
}

UINT64 dg_returnp0plusp1plusp2plusp3 (UINT64 x1, UINT64 x2, UINT64 x3, UINT64 x4)
{
    return (x1 + x2 + x3 + x4);
}

UINT64 dg_returnsumofp0p1p2p3p4 (
    UINT64 x1,
    UINT64 x2,
    UINT64 x3,
    UINT64 x4,
    UINT64 x5)
{
    return (x1 + x2 + x3 + x4 + x5);
}

UINT64 dg_returnsumofp0p1p2p3p4p5 (
    UINT64 x1,
    UINT64 x2,
    UINT64 x3,
    UINT64 x4,
    UINT64 x5,
    UINT64 x6)
{
    return (x1 + x2 + x3 + x4 + x5 + x6);
}

UINT64 dg_returnsumofp0p1p2p3p4p5p6 (
    UINT64 x1,
    UINT64 x2,
    UINT64 x3,
    UINT64 x4,
    UINT64 x5,
    UINT64 x6,
    UINT64 x7)
{
    return (x1 + x2 + x3 + x4 + x5 + x6 + x7);
}

UINT64 dg_returnsumofp0p1p2p3p4p5p6p7 (
    UINT64 x1,
    UINT64 x2,
    UINT64 x3,
    UINT64 x4,
    UINT64 x5,
    UINT64 x6,
    UINT64 x7,
    UINT64 x8)
{
    return (x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8);
}

void testdg_callprocaddress()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
    
    UINT64 x;
    unsigned char* pdatastack;
    UINT64* pdatastacklength;
	
	dg_printzerostring(
        &BHarrayhead,
        (unsigned char*)"testing dg_callprocaddress\n");
	
	// success case 0 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returntestuint64);
    
    if (x != 0x1122998833447766)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 0 parameters success case - got wrong return value from call\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 0 parameters success case - data stack not empty after call\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    // success case 1 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        47); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        1, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnparam0plus1);
    
    if (x != 48)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 1 parameters success case - got wrong return value from call, expected 48, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 1 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 2 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        2, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnparam0plusparam1);
    
    if (x != 77)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 2 parameters success case - got wrong return value from call, expected 77, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 2 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 3 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        3, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnp0plusp1plusp2);
    
    if (x != 100)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 3 parameters success case - got wrong return value from call, expected 100, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 3 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 4 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        4, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnp0plusp1plusp2plusp3);
    
    if (x != 199)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 4 parameters success case - got wrong return value from call, expected 199, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 4 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 5 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        5, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnsumofp0p1p2p3p4);
    
    if (x != 201)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 5 parameters success case - got wrong return value from call, expected 201, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 5 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 6 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        9); // parameter 5 value
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        6, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnsumofp0p1p2p3p4p5);
    
    if (x != 210)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 6 parameters success case - got wrong return value from call, expected 210, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 6 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 7 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        3000); // parameter 6 value
    
    dg_pushdatastack(
        &BHarrayhead,
        9); // parameter 5 value
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        7, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnsumofp0p1p2p3p4p5p6);
    
    if (x != 3210)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 7 parameters success case - got wrong return value from call, expected 3210, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 7 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 8 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        40000); // parameter 7 value
    
    dg_pushdatastack(
        &BHarrayhead,
        3000); // parameter 6 value
    
    dg_pushdatastack(
        &BHarrayhead,
        9); // parameter 5 value
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    x = dg_callprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        8, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returnsumofp0p1p2p3p4p5p6p7);
    
    if (x != 43210)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 8 parameters success case - got wrong return value from call, expected 43210, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddress 8 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


FLOAT64 dg_returntestfloat64()
{
    return (7.13);
}

FLOAT64 dg_returndfparam0plus1(UINT64 p0)
{
    return (FLOAT64(p0 + 1));
}

FLOAT64 dg_returndfparam0plusparam1(
    UINT64 p0,
    UINT64 p1)
{
    return (FLOAT64(p0 + p1));
}

FLOAT64 dg_returndfp0plusp1plusp2(
    UINT64 p0,
    UINT64 p1,
    UINT64 p2)
{
    return (FLOAT64(p0 + p1 + p2));
}

FLOAT64 dg_returndfp0plusp1plusp2plusp3(
    UINT64 p0,
    UINT64 p1,
    UINT64 p2,
    UINT64 p3)
{
    return (FLOAT64(p0 + p1 + p2 + p3));
}

FLOAT64 dg_returndfsumofp0p1p2p3p4(
    UINT64 p0,
    UINT64 p1,
    UINT64 p2,
    UINT64 p3,
    UINT64 p4)
{
    return (FLOAT64(p0 + p1 + p2 + p3 + p4));
}

FLOAT64 dg_returndfsumofp0p1p2p3p4p5(
    UINT64 p0,
    UINT64 p1,
    UINT64 p2,
    UINT64 p3,
    UINT64 p4,
    UINT64 p5)
{
    return (FLOAT64(p0 + p1 + p2 + p3 + p4 + p5));
}

FLOAT64 dg_returndfsumofp0p1p2p3p4p5p6(
    UINT64 p0,
    UINT64 p1,
    UINT64 p2,
    UINT64 p3,
    UINT64 p4,
    UINT64 p5,
    UINT64 p6)
{
    return (FLOAT64(p0 + p1 + p2 + p3 + p4 + p5 + p6));
}

FLOAT64 dg_returndfsumofp0p1p2p3p4p5p6p7(
    UINT64 p0,
    UINT64 p1,
    UINT64 p2,
    UINT64 p3,
    UINT64 p4,
    UINT64 p5,
    UINT64 p6,
    UINT64 p7)
{
    return (FLOAT64(p0 + p1 + p2 + p3 + p4 + p5 + p6 + p7));
}

FLOAT64 dg_returndfoff0plus1(
    FLOAT64 df0)
{
    return (df0 + 1.0);
}

FLOAT64 dg_returndfsumoff0f1(
    FLOAT64 df0,
    FLOAT64 df1)
{
    return(df0 + df1);
}

FLOAT64 dg_returndfsumoff0f1f2(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2)
{
    return(df0 + df1 + df2);
}

FLOAT64 dg_returndfsumoff0f1f2f3(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2,
    FLOAT64 df3)
{
    return(df0 + df1 + df2 + df3);
}

FLOAT64 dg_returndfsumoff0f1f2f3f4(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2,
    FLOAT64 df3,
    FLOAT64 df4)
{
    return(df0 + df1 + df2 + df3 + df4);
}

FLOAT64 dg_returndfsumoff0f1f2f3f4f5(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2,
    FLOAT64 df3,
    FLOAT64 df4,
    FLOAT64 df5)
{
    return(df0 + df1 + df2 + df3 + df4 + df5);
}

FLOAT64 dg_returndfsumoff0f1f2f3f4f5f6(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2,
    FLOAT64 df3,
    FLOAT64 df4,
    FLOAT64 df5,
    FLOAT64 df6)
{
    return(df0 + df1 + df2 + df3 + df4 + df5 + df6);
}

FLOAT64 dg_returndfsumoff0f1f2f3f4f5f6f7(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2,
    FLOAT64 df3,
    FLOAT64 df4,
    FLOAT64 df5,
    FLOAT64 df6,
    FLOAT64 df7)
{
    return(df0 + df1 + df2 + df3 + df4 + df5 + df6 + df7);
}

FLOAT64 dg_returndfsumoff0f1f2f3f4f5f6f7f8(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2,
    FLOAT64 df3,
    FLOAT64 df4,
    FLOAT64 df5,
    FLOAT64 df6,
    FLOAT64 df7,
    FLOAT64 df8)
{
    return(df0 + df1 + df2 + df3 + df4 + df5 + df6 + df7 + df8);
}

FLOAT64 dg_returndfsumoff0f1f2f3f4f5f6f7f8f9(
    FLOAT64 df0,
    FLOAT64 df1,
    FLOAT64 df2,
    FLOAT64 df3,
    FLOAT64 df4,
    FLOAT64 df5,
    FLOAT64 df6,
    FLOAT64 df7,
    FLOAT64 df8,
    FLOAT64 df9)
{
    return(df0 + df1 + df2 + df3 + df4 + df5 + df6 + df7 + df8 + df9);
}

FLOAT64 dg_returndfsumoff10p8(
    UINT64 p0, // rcx
    UINT64 p1, // rdx
    UINT64 p2, // r8
    UINT64 p3, // r9
                 // return stack param 1 - 4 are shadow params
    UINT64 p4,   // return stack param 5
    UINT64 p5,   // return stack param 6
    UINT64 p6,   // return stack param 7
    UINT64 p7,   // return stack param 8
    FLOAT64 df0, // return stack param 9
    FLOAT64 df1, // return stack param 10
    FLOAT64 df2, // etc...
    FLOAT64 df3,
    FLOAT64 df4,
    FLOAT64 df5,
    FLOAT64 df6,
    FLOAT64 df7,
    FLOAT64 df8,
    FLOAT64 df9)
{
    return(df0 + df1 + df2 + df3 + df4 + df5 + df6 + df7 + df8 + df9 +
      ((FLOAT64)(p0 + p1 + p2 + p3 + p4 + p5 + p6 + p7)));
}

FLOAT64 dg_returndfsumoff1p4(
    UINT64 p0,   // rcx
    FLOAT64 df0, // xmm0
    FLOAT64 df1, // xmm1
    FLOAT64 df2, // xmm2
                 // shadow parameters return stack 1 - 4
    FLOAT64 df3) 
{
    return(df0 + df1 + df2 + df3 +
        ((FLOAT64)(p0)));
}

void testdg_calldfpprocaddress()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
    
    UINT64 x;
    FLOAT64 f;
    unsigned char* pdatastack;
    UINT64* pdatastacklength;
	
	dg_printzerostring(
        &BHarrayhead,
        (unsigned char*)"testing dg_calldfpprocaddress\n");
	
	// success case 0 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returntestfloat64,
        0); // number of floating point parameters
    
    if (f != 7.13)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 0 parameters success case - got wrong return value from call\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 0 parameters success case - data stack not empty after call\n");

    }
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_testalignmentdf,
        0); // number of floating point parameters
    
    if ((*((UINT64*)(&f)) & 0xF) != 8 )
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 0 parameters success case - call not 16 byte aligned - 8 after function entry\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 0 parameters success case - data stack not empty after test alignment call\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    // success case 1 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        32); // parameter 0
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        1, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfparam0plus1,
        0); // number of floating point parameters
    
    if (f != 33.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 1 parameters success case - got wrong return value from call, expected 33, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 1 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 2 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        32); // parameter 1
    
    dg_pushdatastack(
        &BHarrayhead,
        64); // parameter 0
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        2, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfparam0plusparam1,
        0);
    
    if (f != 96.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 2 parameters success case - got wrong return value from call, expected 96, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 2 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 3 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        3, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfp0plusp1plusp2,
        0);
    
    if (f != 100.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 3 parameters success case - got wrong return value from call, expected 100, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 3 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 4 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        4, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfp0plusp1plusp2plusp3,
        0);
    
    if (f != 199.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 4 parameters success case - got wrong return value from call, expected 199, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 4 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 5 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        5, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumofp0p1p2p3p4,
        0);
    
    if (f != 201.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 5 parameters success case - got wrong return value from call, expected 201, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 5 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 6 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        9); // parameter 5 value
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        6, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumofp0p1p2p3p4p5,
        0);
    
    if (f != 210.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 6 parameters success case - got wrong return value from call, expected 210, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 6 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 7 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        3000); // parameter 6 value
    
    dg_pushdatastack(
        &BHarrayhead,
        9); // parameter 5 value
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        7, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumofp0p1p2p3p4p5p6,
        0);
    
    if (f != 3210.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 7 parameters success case - got wrong return value from call, expected 3210, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 7 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 8 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        40000); // parameter 7 value
    
    dg_pushdatastack(
        &BHarrayhead,
        3000); // parameter 6 value
    
    dg_pushdatastack(
        &BHarrayhead,
        9); // parameter 5 value
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        8, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumofp0p1p2p3p4p5p6p7,
        0);
    
    if (f != 43210.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 8 parameters success case - got wrong return value from call, expected 43210, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 8 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);

    // success case 1 df parameter
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfoff0plus1,
        1);
    
    if (f != 3.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 1 df parameter success case - got wrong return value from call, expected 3, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 1 df parameter success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    // success case 2 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 0 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1,
        2);
    
    if (f != 6.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 2 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 2 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 3 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 0 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 0 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2,
        3);
    
    if (f != 14.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 3 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 3 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    // success case 4 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 0 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 0 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 0 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2f3,
        4);
    
    if (f != 30.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 4 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 4 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 5 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 0 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 0 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 0 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4040000000000000); // df parameter 0 value = 32
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2f3f4,
        5);
    
    if (f != 62.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 5 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 5 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 6 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 0 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 0 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 0 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4040000000000000); // df parameter 0 value = 32
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4050000000000000); // df parameter 0 value = 64
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2f3f4f5,
        6);
    
    if (f != 126.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 6 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 6 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 7 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 1 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 2 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 3 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4040000000000000); // df parameter 4 value = 32
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4050000000000000); // df parameter 5 value = 64
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4060000000000000); // df parameter 6 value = 128
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2f3f4f5f6,
        7);
    
    if (f != 254.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 7 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 7 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 7 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 1 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 2 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 3 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4040000000000000); // df parameter 4 value = 32
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4050000000000000); // df parameter 5 value = 64
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4060000000000000); // df parameter 6 value = 128
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4070000000000000); // df parameter 7 value = 256
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2f3f4f5f6f7,
        8);
    
    if (f != 510.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 8 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 8 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 9 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 1 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 2 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 3 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4040000000000000); // df parameter 4 value = 32
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4050000000000000); // df parameter 5 value = 64
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4060000000000000); // df parameter 6 value = 128
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4070000000000000); // df parameter 7 value = 256
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4080000000000000); // df parameter 8 value = 512
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2f3f4f5f6f7f8,
        9);
    
    if (f != 1022.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 9 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 9 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 10 df parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 1 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 2 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 3 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4040000000000000); // df parameter 4 value = 32
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4050000000000000); // df parameter 5 value = 64
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4060000000000000); // df parameter 6 value = 128
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4070000000000000); // df parameter 7 value = 256
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4080000000000000); // df parameter 8 value = 512
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4090000000000000); // df parameter 9 value = 1024
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff0f1f2f3f4f5f6f7f8f9,
        10);
    
    if (f != 2046.0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 10 df parameters success case - got wrong return value from call, expected 6, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 10 df parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
    
    // success case 10 FLOAT64 and 8 UINT64 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 0 value = 2
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 1 value = 4
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 2 value = 8
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 3 value = 16
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4040000000000000); // df parameter 4 value = 32
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4050000000000000); // df parameter 5 value = 64
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4060000000000000); // df parameter 6 value = 128
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4070000000000000); // df parameter 7 value = 256
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4080000000000000); // df parameter 8 value = 512
    
    dg_pushdatastack(
        &BHarrayhead,
        0x4090000000000000); // df parameter 9 value = 1024
    
    dg_pushdatastack(
        &BHarrayhead,
        40000); // parameter 7 value
    
    dg_pushdatastack(
        &BHarrayhead,
        3000); // parameter 6 value
    
    dg_pushdatastack(
        &BHarrayhead,
        9); // parameter 5 value
    
    dg_pushdatastack(
        &BHarrayhead,
        2); // parameter 4 value
    
    dg_pushdatastack(
        &BHarrayhead,
        99); // parameter 3 value
    
    dg_pushdatastack(
        &BHarrayhead,
        23); // parameter 2 value
    
    dg_pushdatastack(
        &BHarrayhead,
        33); // parameter 1 value
    
    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        8, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff10p8,
        10); // number of floating point parameters in call
    
    if (f != 45256.0) // 2046.0 + 43210.0
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 10 FLOAT64 and 8 UINT64 parameters success case - got wrong return value from call, expected 45256, got ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 10 FLOAT64 and 8 UINT64 parameters success case - data stack not empty after call, actual length in bytes = ");
        
        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);

    // success case 4 FLOAT64 and 1 UINT64 parameters
    dg_initbuffers(&BHarrayhead);

    dg_pushdatastack(
        &BHarrayhead,
        0x4000000000000000); // df parameter 3 value = 2

    dg_pushdatastack(
        &BHarrayhead,
        0x4010000000000000); // df parameter 2 value = 4

    dg_pushdatastack(
        &BHarrayhead,
        0x4020000000000000); // df parameter 1 value = 8

    dg_pushdatastack(
        &BHarrayhead,
        0x4030000000000000); // df parameter 0 value = 16

    dg_pushdatastack(
        &BHarrayhead,
        44); // parameter 0 value

    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of df parameters in call

    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call

    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call

    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    f = dg_calldfpprocaddress(
        (UINT64*)pdatastack, // pointer to parameters
        1, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returndfsumoff1p4,
        4); // number of floating point parameters in call

    if (f != 74.0) 
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 4 FLOAT64 and 1 UINT64 parameters success case - got wrong return value from call, expected 45256, got ");

        dg_writestdoutuinttodec(
            &BHarrayhead,
            (UINT64)f);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_calldfpprocaddress 4 FLOAT64 and 1 UINT64 parameters success case - data stack not empty after call, actual length in bytes = ");

        dg_writestdoutuinttodec(
            &BHarrayhead,
            x);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_callprocaddressretuint128()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
    
    UINT64 x;
    UINT64 py[2];
    unsigned char* pdatastack;
    UINT64* pdatastacklength;
	
	dg_printzerostring(
        &BHarrayhead,
        (unsigned char*)"testing dg_callprocaddressretuint128\n");
	
	// success case 0 parameters
	dg_initbuffers(&BHarrayhead);
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be number of parameters in call
    
    dg_pushdatastack(
        &BHarrayhead,
        0); // technically should be address of function to call
    
    pdatastack = dg_getpbuffer(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);
	
    py[0] = dg_callprocaddressretuint128(
        (UINT64*)pdatastack, // pointer to parameters
        0, // number of parameters in call
        pdatastacklength,
        (UINT64*)&dg_returntestuint128,
        &(py[1]));
    
    if ((py[0] != -5) || (py[1] != -1))
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddressretuint128 0 parameters success case - got wrong return value from call, expected -5 lo, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, py[0]);
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)",\n  and expected -1 hi, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, py[1]);
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(
            &BHarrayhead,
            (unsigned char*)"FAIL! testing dg_callprocaddressretuint128 0 parameters success case - data stack not empty after call\n");

    }

    dg_printzerostring(
        &BHarrayhead,
        (unsigned char*)" ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}

void testcompiledemptysubroutine()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compiled empty subroutine\n");
	
	// calling empty compiled subroutine
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
		
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine calling empty compiled subroutine case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine calling empty compiled subroutine case - could not get current compile buffer's length\n");
		return;
	}

	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine calling empty compiled subroutine case - could not compile init locals\n");
		return;
	}
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine calling empty compiled subroutine case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine calling empty compiled subroutine case - got errors doing dg_callbuffer, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_freeallbuffers(&BHarrayhead);
        return;
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


void testcompiledstackalign()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compiled empty subroutine with stack alignment\n");
	
	// calling empty compiled subroutine with stack alignment
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine with stack alignment success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine with stack alignment success case - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine with stack alignment success case - could not compile init locals\n");
		return;
	}
	
	dg_compilealignretstack(&BHarrayhead, 0);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine with stack alignment success case - could not compile alignment\n");
		return;
	}
	
//	dg_compileundoalignretstack(&BHarrayhead);
	
//	if (BHarrayhead.errorcount != 0)
//	{
//		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine with stack alignment success case - could not compile undo alignment\n");
//		return;
//	}
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine with stack alignment success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled empty subroutine with stack alignment success case - got errors doing dg_callbuffer, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}

void testcompileinitlocalreturnpBHarrayhead()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing compile init locals return pBHarrayhead\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return pBHarrayhead success case - could not get current compile buffer\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return pBHarrayhead success case - could not get current compile buffer's length\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    // compiling a forth routine that calls DUP ( : unnamed DUP ; )
    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return pBHarrayhead success case - could not compile init locals\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_param1reg,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return pBHarrayhead success case - could not compile mov rcx to rax\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    dg_compileexitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return pBHarrayhead success case - could not compile exit locals\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    // now the real test, does it crash?
    x = dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return pBHarrayhead success case - got errors doing dg_callbuffer, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    // seeing if it worked
    if (x != ((UINT64)(&BHarrayhead)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return pBHarrayhead success case - did not get pBHarrayhead back after call, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)" .. address that was supposed to be called =  ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)dg_getpbufferoffset(&BHarrayhead, mycurrentcompilebuffer, mystartoffset));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testcompileinitlocalreturnframepBHarrayhead()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing compile init locals return frame pBHarrayhead\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return frame pBHarrayhead success case - could not get current compile buffer\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return frame pBHarrayhead success case - could not get current compile buffer's length\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    // compiling a forth routine that calls DUP ( : unnamed DUP ; )
    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return frame pBHarrayhead success case - could not compile init locals\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    dg_compilemovbracketrbpd8toreg(
        &BHarrayhead,
        dg_rax,
        -0x10); // -0x10

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return frame pBHarrayhead success case - could not compile mov rcx to rax\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    dg_compileexitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return frame pBHarrayhead success case - could not compile exit locals\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    // now the real test, does it crash?
    x = dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return frame pBHarrayhead success case - got errors doing dg_callbuffer, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    // seeing if it worked
    if (x != ((UINT64)(&BHarrayhead)))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile init locals return frame pBHarrayhead success case - did not get pBHarrayhead back after call, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)" .. address that was supposed to be called =  ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)dg_getpbufferoffset(&BHarrayhead, mycurrentcompilebuffer, mystartoffset));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testcompilecallforthroutineincore()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	UINT64 x = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compiled call forth routine in core\n");
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine that calls DUP ( : unnamed DUP ; )
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - could not compile init locals\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthdup));
    // dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthgothere));
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - could not compile exit locals\n");
		return;
	}
	
	// setting data stack up for test
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - data stack not empty for test as expected\n");
		return;
	}
					   
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x76757473);
					   
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - could not push test number to data stack\n");
		return;
	}
    
    // dg_hexdumpsegment(
    //    &BHarrayhead,
    //    dg_getpbufferoffset(&BHarrayhead, mycurrentcompilebuffer, mystartoffset),
    //    64);
					
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  dg_callbuffer returned ok\n");
	
	// seeing if it worked
	 x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
					   
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - data stack length not correct after call\n");
		return;
	}
					   
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
					   
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
					   
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core success case - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
					   					   
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


void testcompilecallforthroutineincoreatvariousaligments()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	UINT64 x = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compiled call forth routine in core at various alignments\n");
	
	// success case +1 items on stack
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine that calls DUP ( : unnamed DUP ; )
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - could not compile init locals\n");
		return;
	}
    
    dg_compilealignretstack(
        &BHarrayhead,
        1);
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead);
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthdup));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - could not compile exit locals\n");
		return;
	}
	
	// setting data stack up for test
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - data stack not empty for test as expected\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x76757473);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - could not push test number to data stack\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +1 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	
	// success case +2 items on stack
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine that calls DUP ( : unnamed DUP ; )
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - could not compile init locals\n");
		return;
	}
    
    dg_compilealignretstack(
        &BHarrayhead,
        7);
    
    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthdup));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - could not compile exit locals\n");
		return;
	}
	
	// setting data stack up for test
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - data stack not empty for test as expected\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x76757473);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - could not push test number to data stack\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +2 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	
	// success case +3 items on stack
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine that calls DUP ( : unnamed DUP ; )
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - could not compile init locals\n");
		return;
	}
    
    dg_compilealignretstack(
        &BHarrayhead,
        8);
    
    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);
    
    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead);
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthdup));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - could not compile exit locals\n");
		return;
	}
	
	// setting data stack up for test
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - data stack not empty for test as expected\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x76757473);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - could not push test number to data stack\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +3 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	
	// success case +4 items on stack
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine that calls DUP ( : unnamed DUP ; )
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - could not compile init locals\n");
		return;
	}
    
    dg_compilealignretstack(
        &BHarrayhead,
        9);
    
    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);
    
    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);
    
    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthdup));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - could not compile exit locals\n");
		return;
	}
	
	// setting data stack up for test
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - data stack not empty for test as expected\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x76757473);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - could not push test number to data stack\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call forth routine in core at various alignments success case +4 - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}

/*
// this tests the compile alignment code for the four cases
//   case with 1 parameter already thoroughly tested in testcompilecallforthroutineincoreatvariousaligments
//   this is just a crash test
void testcompilecallsubroutineswithvariousnumberofparameters()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
//	Bufferhandle* pBH = NULL;
	
//	const char* pError = NULL;
	UINT32 mycurrentcompilebuffer = 0;
	UINT32 mystartoffset = 0;
//	UINT32 x = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compiled call subroutine with various number of parameters\n");
	
	// success case 0 parameters
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 0 parameters - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 0 parameters - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 0 parameters - could not compile init locals\n");
		return;
	}
	
	//dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	dg_compilecalladdress(&BHarrayhead, (UINT64)(&dg_getpagesize));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 0 parameters - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	
	// success case 1 parameter
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 1 parameter - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 1 parameter - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 1 parameter - could not compile init locals\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 1 parameter - could not compile push paramater to return stack\n");
		return;
	}
	
	dg_compilecalladdress(&BHarrayhead, (UINT64)(&dg_getpagesize));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 1 parameter - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	
	// success case 2 parameters
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 2 parameters - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 2 parameters - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 2 parameters - could not compile init locals\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 2 parameters - could not compile push paramater to return stack\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 2 parameters - could not compile push paramater to return stack\n");
		return;
	}
	
	dg_compilecalladdress(&BHarrayhead, (UINT64)(&dg_getpagesize));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 2 parameters - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	
	// success case 3 parameters
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 3 parameters - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 3 parameters - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 3 parameters - could not compile init locals\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 3 parameters - could not compile push paramater to return stack\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 3 parameters - could not compile push paramater to return stack\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // doesnt matter what is pushed
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 3 parameters - could not compile push paramater to return stack\n");
		return;
	}
	
	dg_compilecalladdress(&BHarrayhead, (UINT64)(&dg_getpagesize));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call subroutine with various number of parameters success case 3 parameters - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	
}
*/


void testcompilecalloffsetinsamebuffer()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset1 = 0;
	UINT64 mystartoffset2 = 0;
	UINT64 x = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compiled call routine at offset in same buffer\n");
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset1 = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to call that does ( : unnamed DUP ; )
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not compile init locals\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // pushing pBHarrayhead for dg_forthdup
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthdup));
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not compile exit locals\n");
		return;
	}
	
	mystartoffset2 = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to call the forth routine that was just compiled
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not compile init locals\n");
		return;
	}
	
	dg_compilepushpBHarrayheadtoret(&BHarrayhead); // pushing pBHarrayhead for the new forth routine
	
	dg_compilecalloffsetinsamebuffer(&BHarrayhead, mystartoffset1);
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not compile exit locals\n");
		return;
	}
	
	// setting data stack up for test
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - data stack not empty for test as expected\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x76757473);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - could not push test number to data stack\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset2);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x76757473)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiled call routine at offset in same buffer success case - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}



void testdg_compilepushtodatastack()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	UINT64 x = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compile push to data stack\n");
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to push a number to the data stack
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - could not compile init locals\n");
		return;
	}
	
	dg_compilepushntoret(&BHarrayhead, 0x12348765); // pushing number to return stack as parameter 1
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - could not compile push to return\n");
		return;
	}
	
	dg_compilepushdatastack(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - could not compile push to data stack\n");
		return;
	}
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x12348765)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push to data stack success case - top number on data stack after calling compiled call to DUP incorrect, expected 0x12348765, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
		return;
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilepushntodatastack()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	UINT64 x = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compile push n to data stack\n");
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push n to data stack success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push n to data stack success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to push a number to the data stack
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push n to data stack success case - could not compile init locals\n");
		return;
	}
	
	dg_compilepushntodatastack(&BHarrayhead, 0x123487659abc0fed);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push n to data stack success case - could not compile push to data stack\n");
		return;
	}
	
	// no need to drop parameter since exit locals fixes stack
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push n to data stack success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push n to data stack success case - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x123487659abc0fed)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compile push n to data stack success case - top number on data stack after calling compiled call to DUP incorrect\n");
		return;
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_initjumpbuffer()
{
    Bufferhandle myfakebharrayhead; // for the first couple dg_printzerostrings

	// have to put jumpbuffer in a dg_malloced buffer because mac os x does not allow execution of code on return stack
	const char* pError = NULL;
	Bufferhandle* pBHarrayhead;
	
	UINT64 pagesize = dg_getpagesize();
	UINT64 truesize = dg_gettruesize();  // gets size of memory needed to hold buffer handle array head + jump buffer
	
	// mac os x requires memory to be allocated in units of system pagesize
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mycontinueoffset = 0;
    UINT64 mystartoffset, mystartoffset2;
    UINT64 x;
				
    dg_initpbharrayhead(&myfakebharrayhead);
	
	dg_printzerostring(&myfakebharrayhead,  (unsigned char*)"testing dg_initjumpbuffer\n");

    // need a dg_malloc buffer for BHarrayhead and jumpbuffer in order to get execute permission for both windows and mac
    pError = dg_malloc(
        (void**)&pBHarrayhead,
        truesize,
        dg_success);

    if (pError != dg_success)
    {
        dg_printzerostring(&myfakebharrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer - got error allocating memory for test \n");
    }

    dg_initpbharrayhead(pBHarrayhead);
	
	// success case
	dg_initbuffers(pBHarrayhead);
	
	dg_initvariables(pBHarrayhead);
	
	dg_initjumpbuffer(pBHarrayhead);

    // dg_callcoreforthroutine(
    //    pBHarrayhead,
    //    (UINT64)(((unsigned char*)pBHarrayhead) + sizeof(Bufferhandle)));
	
	// change current compile buffer to one I know the size of
	mycurrentcompilebuffer = dg_newbuffer(pBHarrayhead, 10000, 100000, &pError, FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not get current compile buffer\n");
		return;
	}
	
	dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, mycurrentcompilebuffer);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not get current compile buffer\n");
		return;
	}

    mystartoffset2 = dg_getbufferlength(pBHarrayhead, mycurrentcompilebuffer);

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(pBHarrayhead);

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile init locals\n");
        return;
    }
	
	// compiling a partial forth routine for a jump buffer continue
    mycontinueoffset = dg_getbufferlength(pBHarrayhead, mycurrentcompilebuffer);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not get current compile buffer's length\n");
		return;
	}
    /*
    dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_forthgothere));

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile init locals\n");
        return;
    }
    
    dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_forthgothere));

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile init locals\n");
        return;
    }
    */

    dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_forthdup));  // compile call core does the alignment
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile init locals\n");
		return;
	}
    
    dg_compileexitlocals(pBHarrayhead);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile exit locals\n");
		return;
	}

    // testing calling the partial forth routine
    dg_pushdatastack(pBHarrayhead, 8362378);

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - got an error pushing to the data stack\n");
        return;
    }

    dg_callbuffer(pBHarrayhead, mycurrentcompilebuffer, mystartoffset2);

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - calling partial test forth routine\n");
        return;
    }

    x = dg_popdatastack(pBHarrayhead);

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - got an error popping the data stack\n");
        return;
    }

    if (x != 8362378)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - 1st number popped from partial forth routine incorrect\n");
        return;
    }

    x = dg_popdatastack(pBHarrayhead);

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - got an error popping the data stack 2nd time\n");
        return;
    }

    if (x != 8362378)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - 2nd number popped from partial forth routine incorrect\n");
        return;
    }

    mystartoffset = dg_getbufferlength(pBHarrayhead, mycurrentcompilebuffer);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not get current compile buffer's length second time\n");
		return;
	}

    dg_printzerostring(pBHarrayhead, (unsigned char*)" - finished testing compiled partial forth routine\n");
    
    // compiling a forth routine to use the jump buffer
	dg_compileinitlocals(pBHarrayhead);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile init locals\n");
		return;
	}

    // dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_forthgothere));

    dg_compilealignretstack(
        pBHarrayhead,
        2);

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile alignment code\n");
        return;
    }
    
    dg_compilepushntoret(
        pBHarrayhead,
        mycontinueoffset);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile push start offset to return\n");
		return;
	}
    
    dg_compilepushntoret(
        pBHarrayhead,
        mycurrentcompilebuffer);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile push current compile buffer to return\n");
		return;
	}
#ifdef DGLU_OS_WIN64
    dg_compilesubn8fromrsp(   // for shadow guard in Win64
        pBHarrayhead,
        0x20);
#endif
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)"\x48\x8B\x45\xF0", // [RBP-0x10]->RAX
        4);

    // dg_compilemovbracketrbpd8toreg(
    //    pBHarrayhead,
    //    dg_rax,
    //    -0x10);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile pBHarrayhead->rax\n");
		return;
	}
    
    dg_compileaddn32torax (
        pBHarrayhead,
        sizeof(Bufferhandle));

    if (pBHarrayhead->errorcount != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile init locals\n");
        return;
    }

    dg_compilejumptorax(pBHarrayhead);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not compile jump rax\n");
		return;
	}
    
    dg_pushdatastack(pBHarrayhead, 0x1122334499887766);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - could not push test number to data stack\n");
		return;
	}
    
    /*
    dg_printzerostring(pBHarrayhead, (unsigned char*)"address of dg_getpbufferoffset = ");
    dg_writestdoutuint64tohex(pBHarrayhead, (UINT64)&dg_getpbufferoffset);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    dg_hexdumpsegment (
        pBHarrayhead,
        (unsigned char*)pBHarrayhead + sizeof(Bufferhandle),
        0x40);
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    */
    
    dg_callbuffer(pBHarrayhead, mycurrentcompilebuffer, mystartoffset);
    /*
    __try
    {
        dg_callbuffer(pBHarrayhead, mycurrentcompilebuffer, mystartoffset);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - got an exception trying to call the compiled code\n");
    }
    */
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - got an error calling function that calls DUP through a jump buffer, got ");
        dg_forthdoterrors(pBHarrayhead);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
		return;
	}
    
    x = dg_popdatastack(pBHarrayhead);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - got an error popping top result from data stack\n");
		return;
	}
    
    if (x != 0x1122334499887766)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - top result not correct\n");
		return;
    }
	
    x = dg_popdatastack(pBHarrayhead);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - got an error popping second result from data stack\n");
		return;
	}
    
    if (x != 0x1122334499887766)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - second result not correct\n");
		return;
    }
    
    x = dg_getbufferlength(pBHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - error getting data stack length\n");
		return;
	}
    
    if (x != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing dg_initjumpbuffer success case - data stack not empty after test\n");
		return;
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)" ... test done\n");
    
    dg_clearerrors(pBHarrayhead);
	
	dg_freeallbuffers(pBHarrayhead);
    
    pError = dg_free((void*)pBHarrayhead, truesize, dg_success);
}


// if this test fails any part, it will leak memory
void testdg_compilesafecall()
{
    Bufferhandle myfakebharrayhead; // for the first couple dg_printzerostrings
	const char* pError = NULL;
	Bufferhandle* pBHarrayhead;
	
	UINT64 pagesize = dg_getpagesize();
	UINT64 truesize;   // gets size of memory needed to hold buffer handle array head + jump buffer
	
	// mac os x requires memory to be allocated in units of system pagesize
    // windows does now too
    truesize = dg_gettruesize();
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
    
    UINT64 x; 

    dg_initpbharrayhead(&myfakebharrayhead);
	
	dg_printzerostring(&myfakebharrayhead,  (unsigned char*)"testing compile safe call\n");

    // need a dg_malloc buffer for BHarrayhead and jumpbuffer in order to get execute permission for both windows and mac
    pError = dg_malloc(
        (void**)&pBHarrayhead,
        truesize,
        dg_success);

    if (pError != dg_success)
    {
        dg_printzerostring(&myfakebharrayhead, (unsigned char*)"FAIL! testing compile safe call - got error allocating memory for test \n");
    }

    dg_initpbharrayhead(pBHarrayhead);
	
	// success case
	dg_initbuffers(pBHarrayhead);
	
	dg_initvariables(pBHarrayhead);
	
	dg_initjumpbuffer(pBHarrayhead);
	
	// change current compile buffer to one I know the size of
	mycurrentcompilebuffer = dg_newbuffer(pBHarrayhead, dg_getpagesize(), 8 * dg_getpagesize(), &pError, FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not get current compile buffer\n");
		return;
	}
	
	dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, mycurrentcompilebuffer);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(pBHarrayhead, mycurrentcompilebuffer);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to safe call a core routine that moves (by growing to more than the current size) the current compile buffer
	//  since this routine is executing in the current compile buffer, a safe call is necessary for the core routine to return
	//  to the correct address
	dg_compileinitlocals(pBHarrayhead);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not compile init locals\n");
		return;
	}

    // dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_forthgothere));
	
	dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&dg_forthgrowbuffer); // bufferoffset
    // dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&dg_forthgothere); // bufferoffset
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not push address of dg_forthgrowbuffer to data stack\n");
		return;
	}
		
	dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, DG_CORE_BUFFERID); // bufferid
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not push core buffer id to data stack\n");
		return;
	}
	
	//seeing if frame changed during safe call
	//dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_showframe));

    // dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_forthgothere));
	
	dg_forthcompilesafecallbuffer(pBHarrayhead);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not push core buffer id to data stack\n");
		return;
	}
    
    if (dg_getbufferlength(pBHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - data stack not empty after call\n");
		return;
    }
    
    dg_compilepushntodatastack(
        pBHarrayhead,
        0x1287349955887722);

    // dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_forthgothere));
	
	//dg_compilecallcore(pBHarrayhead, (UINT64)(&dg_showframe));
	
	// if calling dg_growbuffer does not change the buffer's base address, you might be able to manually allocate a new buffer, and copy the data from one to the other
	
	dg_compileexitlocals(pBHarrayhead);
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash? pushing parameters and making the call
	dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, dg_getpagesize()); // growby
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not push growby to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, mycurrentcompilebuffer); // buffer id
	
	if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - could not push current compile buffer id to data stack\n");
		return;
	}
		
	dg_callbuffer(pBHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// if it didn't crash, it worked
	//   could also check to make sure base address of buffer changed and if it didnt, do an alternate test where buffer contents are copied to new address
	
    x = dg_popdatastack(pBHarrayhead);
    
    if (pBHarrayhead->errorcount != 0)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - got an error popping the data stack\n");
		return;
	}
    
    if (x != 0x1287349955887722)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"FAIL! testing compile safe call success case - result of compiled safe called forth routine incorrect\n");
		return;
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)" ... test done\n");
    
	dg_clearerrors(pBHarrayhead);
	
	dg_freeallbuffers(pBHarrayhead);

    pError = dg_free((void*)pBHarrayhead, truesize, dg_success);
}


/*
void testdg_forthcompilegetolderrorcount()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
//	const char* pError = NULL;
	UINT32 mycurrentcompilebuffer = 0;
	UINT32 mystartoffset = 0;
	
	UINT32 x=0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthcompilegetolderrorcount\n");
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to push pointer to and length of a copy of a string to the data stack
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case - could not compile init locals\n");
		return;
	}
	
	dg_forthcompilegetolderrorcount(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case - could not do dg_forthcompilegetolderrorcount, got errors:\n");
		dg_forthdoterrors(&BHarrayhead);
		return;
	}	
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked with no errors on the stack
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 1*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case no errors - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case no errors - top number on data stack after executed compiled string code incorrect, length not same as source string\n");
		return;
	}
	
	// seeing if it worked with an error on the stack
	dg_pusherror(&BHarrayhead, dg_mallocname);
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 1*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case one error - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case one error - top number on data stack after executed compiled string code incorrect, length not same as source string\n");
		return;
	}
	
	// seeing if it worked with two errors on the stack
	dg_pusherror(&BHarrayhead, dg_mallocname);
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 1*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case two errors - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthcompilegetolderrorcount success case two errors - top number on data stack after executed compiled string code incorrect, length not same as source string\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}
*/

/*
void testdg_packmodrslashm()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
	unsigned char c = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_packmodrslashm\n");
	
	// mode reg1orn reg2
	c = dg_packmodrslashm(0,0,0);
	
	if (c!= 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 0 0 case, expected 0, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(0,0,1);
	
	if (c!= 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 0 1 case, expected 1, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(0,0,2);
	
	if (c!= 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 0 2 case, expected 2, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(0,0,7);
	
	if (c!= 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 0 7 case, expected 7, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(0,0,8);
	
	if (c!= 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 0 8 case, expected 0, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(0,1,0);
	
	if (c!= 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 1 0 case, expected 8, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(0,7,0);
	
	if (c!= 0x38)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 7 0 case, expected 0x38, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(0,8,0);
	
	if (c!= 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 0 8 0 case, expected 0, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(1,0,0);
	
	if (c!= 0x40)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 1 0 0 case, expected 0x40, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(3,0,0);
	
	if (c!= 0xC0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 3 0 0 case, expected 0xC0, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(4,0,0);
	
	if (c!= 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 4 0 0 case, expected 0, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(3,7,7);
	
	if (c!= 0xff)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 3 7 7 case, expected 0xff, didnt get expected result.\n");
	}
	
	c = dg_packmodrslashm(1,1,1);
	
	if (c!= 0x49)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packmodrslashm - 1 1 1 case, expected 0x49, didnt get expected result.\n");
	}
}
*/

/*
void testdg_packsib ()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
	unsigned char c = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_packsib\n");
	
	// basereg scaleofindexreg indexreg  -> scale index base
	//                                         --   ---  ---
	c = dg_packsib(0, 0, 0);
	
	if (c!= 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 0 0 0 case, expected 0, didnt get expected result.\n");
	}
	
	c = dg_packsib(1, 0, 0);
	
	if (c!= 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 1 0 0 case, expected 1, didnt get expected result.\n");
	}
	
	c = dg_packsib(7, 0, 0);
	
	if (c!= 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 7 0 0 case, expected 7, didnt get expected result.\n");
	}
	
	c = dg_packsib(8, 0, 0);
	
	if (c!= 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 8 0 0 case, expected 0, didnt get expected result.\n");
	}
	
	c = dg_packsib(0, 0, 1);
	
	if (c!= 0x08)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 0 0 1 case, expected 8, didnt get expected result.\n");
	}
	
	c = dg_packsib(0, 0, 7);
	
	if (c!= 0x38)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 0 0 7 case, expected 0x38, didnt get expected result.\n");
	}
	
	c = dg_packsib(0, 0, 8);
	
	if (c!= 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 0 0 8 case, expected 0, didnt get expected result.\n");
	}
	
	c = dg_packsib(0, 1, 0);
	
	if (c!= 0x40)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 0 1 0 case, expected 0x40, didnt get expected result.\n");
	}
	
	c = dg_packsib(0, 3, 0);
	
	if (c!= 0xC0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 0 3 0 case, expected 0xC0, didnt get expected result.\n");
	}
	
	c = dg_packsib(7, 3, 7);
	
	if (c!= 0xff)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 7 3 7 case, expected 0xff, didnt get expected result.\n");
	}
	
	c = dg_packsib(1, 1, 1);
	
	if (c!= 0x49)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packsib - 1 1 1 case, expected 0x49, didnt get expected result.\n");
	}
	
}
*/


void testdg_forthsquotes()
{
    Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
	Bufferhandle* pBH = NULL;
	
	const char* pError = NULL;
	
	UINT64 mycurrentcompilebuffer;
	UINT64 mystartoffset;
	UINT64 x;

    unsigned char* pbuffer;
    UINT64* pbufferlength;
	
	UINT64 mycurrentinterpretbuffer;
	unsigned char c;
/*
    unsigned char pbuf[100];
    UINT64 i;

    for (i = 0; i < 100; i++)
    {
        pbuf[i] = 0x90;
    }
*/	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsquotes\n");
	
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not get current compile buffer\n");
		return;
	}

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"current compile buffer = ");
    // dg_writestdoutuinttodec(&BHarrayhead, mycurrentcompilebuffer);
    // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not get current compile buffer's length\n");
		return;
	}
	
	mycurrentinterpretbuffer = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not create a new interpret buffer\n");
		return;
	}

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"current interpret buffer = ");
    // dg_writestdoutuinttodec(&BHarrayhead, mycurrentinterpretbuffer);
    // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, mycurrentinterpretbuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not set current interpret buffer\n");
		return;
	}
	
	dg_pushbuffersegment (&BHarrayhead, mycurrentinterpretbuffer, 20, (unsigned char*)"abcdefghijklmno\"qrst");
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not push test string to current interpret buffer\n");
		return;
	}
	
	// set current offset for parse to 6th character
	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[mycurrentinterpretbuffer] );
	
	pBH->currentoffset = 6;
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not compile init locals\n");
		return;
	}
	
	dg_forthsquotes (&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not do dg_forthsquotes\n");
		return;
	}
    
    /*    
    dg_pushbuffersegment(
        &BHarrayhead,
        mycurrentcompilebuffer,
        73,
        (unsigned char*)pbuf);
    */
    
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - could not compile exit locals\n");
		return;
	}
    /*
    dg_forthcr(&BHarrayhead);

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pbufferlength);

    dg_hexdumpsegment(
        &BHarrayhead,
        pbuffer + mystartoffset,
        *pbufferlength - mystartoffset);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n length = ");
    dg_writestdoutuinttodec(&BHarrayhead, *pbufferlength - mystartoffset);
    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	*/
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
    /*
    dg_forthcr(&BHarrayhead);

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pbufferlength);

    dg_hexdumpsegment(
        &BHarrayhead,
        pbuffer + mystartoffset,
        *pbufferlength - mystartoffset);
	*/
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - got error executing compiled test routine\n");
		return;
	}
	
	if (pBH->currentoffset != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - interpret buffer's final current offset not correct, expected 16 got ");
		dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset != 16);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - length of copied string segment wrong value, expected 8, got ");
		dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	c = ((unsigned char*)x)[0];
	
	if (c != 'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - 1st character of copied string incorrect, expected g, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        // dg_hexdumpsegment(
        //    &BHarrayhead,
        //    (unsigned char*)x,
        //    9);
	}
	
	c = ((unsigned char*)x)[1];
	
	if (c != 'h')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - 2nd character of copied string incorrect, expected h, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	c = ((unsigned char*)x)[8];
	
	if (c != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthsquotes success case - last character of copied string incorrect, expected o, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
    dg_clearerrors(&BHarrayhead);   
	dg_freeallbuffers(&BHarrayhead);
}



void testdg_forthosquotes()
{
    Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
	Bufferhandle* pBH = NULL;
	
	const char* pError = NULL;
	
	UINT64 mycurrentcompilebuffer;
	UINT64 mystartoffset;
	UINT64 x;
	
	UINT64 mycurrentinterpretbuffer;
	unsigned char c;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthosquotes\n");
	
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - could not get current compile buffer's length\n");
		return;
	}
	
	mycurrentinterpretbuffer = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - could not create a new interpret buffer\n");
		return;
	}
	
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, mycurrentinterpretbuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - could not set current interpret buffer\n");
		return;
	}
	
	dg_pushbuffersegment (&BHarrayhead, mycurrentinterpretbuffer, 20, (unsigned char*)"abcdefghijklmno\"qrst");
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - could not push test string to current interpret buffer\n");
		return;
	}
	
	// set current offset for parse to 6th character
	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[mycurrentinterpretbuffer] );
	
	pBH->currentoffset = 6;
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - could not compile init locals\n");
		return;
	}
	
	dg_forthosquotes (&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - could not compile init locals\n");
		return;
	}
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortohsquotes success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - got error executing compiled test routine\n");
		return;
	}
	
	if (pBH->currentoffset != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - interpret buffer's final current offset not correct, expected 16 got ");
		dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - length of copied string segment wrong value, expected 8, got ");
		dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != mycurrentcompilebuffer)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - expected bufferid to be data stack buffer id, got ");
		dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	// x should be offset
	x = (UINT64)dg_getpbufferoffset(&BHarrayhead, mycurrentcompilebuffer, x);
	
	c = ((unsigned char*)x)[0];
	
	if (c != 'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - 1st character of copied string incorrect, expected g, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	c = ((unsigned char*)x)[1];
	
	if (c != 'h')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - 2nd character of copied string incorrect, expected h, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	c = ((unsigned char*)x)[8];
	
	if (c != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_forthosquotes success case - last character of copied string incorrect, expected o, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
    dg_clearerrors(&BHarrayhead);   
	dg_freeallbuffers(&BHarrayhead);
}



void testdg_fortho0quotes()
{
    Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
	Bufferhandle* pBH = NULL;
	
	const char* pError = NULL;
	
	UINT64 mycurrentcompilebuffer;
	UINT64 mystartoffset;
	UINT64 x;
	
	UINT64 mycurrentinterpretbuffer;
	unsigned char c;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_fortho0quotes\n");
	
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - could not get current compile buffer's length\n");
		return;
	}
	
	mycurrentinterpretbuffer = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, FORTH_FALSE);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - could not create a new interpret buffer\n");
		return;
	}
	
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, mycurrentinterpretbuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - could not set current interpret buffer\n");
		return;
	}
	
	dg_pushbuffersegment (&BHarrayhead, mycurrentinterpretbuffer, 20, (unsigned char*)"abcdefghijklmno\"qrst");
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - could not push test string to current interpret buffer\n");
		return;
	}
	
	// set current offset for parse to 6th character
	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[mycurrentinterpretbuffer] );
	
	pBH->currentoffset = 6;
	
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - could not compile init locals\n");
		return;
	}
	
	dg_fortho0quotes (&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - could not compile init locals\n");
		return;
	}
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortoh0quotes success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - got error executing compiled test routine\n");
		return;
	}
	
	if (pBH->currentoffset != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - interpret buffer's final current offset not correct, expected 16 got ");
		dg_writestdoutuinttodec(&BHarrayhead, pBH->currentoffset);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != mycurrentcompilebuffer)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - expected bufferid to be data stack buffer id, got ");
		dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	// x should be offset
	x = (UINT64)dg_getpbufferoffset(&BHarrayhead, mycurrentcompilebuffer, x);
	
	c = ((unsigned char*)x)[0];
	
	if (c != 'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - 1st character of copied string incorrect, expected g, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	c = ((unsigned char*)x)[1];
	
	if (c != 'h')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - 2nd character of copied string incorrect, expected h, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	c = ((unsigned char*)x)[8];
	
	if (c != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - last character of copied string incorrect, expected o, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	c = ((unsigned char*)x)[9];
	
	if (c != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_fortho0quotes success case - last character of copied string incorrect, expected o, got ");
		dg_writestdout(&BHarrayhead, &c, 1);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_printzerostring(&BHarrayhead, (unsigned char*)" ... test done\n");
	
    dg_clearerrors(&BHarrayhead);   
	dg_freeallbuffers(&BHarrayhead);
}



void testdg_packtwobytevex()
{
    Bufferhandle BHarrayhead;
    UINT64 x;
    
    dg_initpbharrayhead(&BHarrayhead);
    
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_packtwobytevex\n");
    
    x = dg_packtwobytevex (
        0, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 8,9
        0, // 0 = 128, 1 = 256                        bit 10
        0, // 0-15  // gets inverted                  bits 11-14
        0); // 0 or 1  // gets inverted               bit 15
    
    if (x != 0xF8C5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packtwobytevex success 0 0 0 0 case - expected 0xF8C5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packtwobytevex (
        0, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        0, // 0 = 128, 1 = 256
        15, // 0-15
        0); // 0 or 1
    
    if (x != 0x80C5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packtwobytevex success 0 0 15 0 case - expected 0x80C5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_packtwobytevex (
        0, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 8,9
        0, // 0 = 128, 1 = 256                        bit 10
        15, // 0-15  // gets inverted                  bits 11-14
        1); // 0 or 1  // gets inverted               bit 15
    
    if (x != 0x00C5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packtwobytevex success 0 0 15 1 case - expected 0x00C5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packtwobytevex (
        0, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 8,9
        1, // 0 = 128, 1 = 256                        bit 10
        15, // 0-15  // gets inverted                  bits 11-14
        1); // 0 or 1  // gets inverted               bit 15
    
    if (x != 0x04C5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packtwobytevex success 0 1 15 1 case - expected 0x04C5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packtwobytevex (
        2, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 8,9
        1, // 0 = 128, 1 = 256                        bit 10
        15, // 0-15  // gets inverted                  bits 11-14
        1); // 0 or 1  // gets inverted               bit 15
    
    if (x != 0x06C5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packtwobytevex success 2 1 15 1 case - expected 0x06C5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packtwobytevex (
        3, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 8,9
        1, // 0 = 128, 1 = 256                        bit 10
        15, // 0-15  // gets inverted                  bits 11-14
        1); // 0 or 1  // gets inverted               bit 15
    
    if (x != 0x07C5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packtwobytevex success 2 1 15 1 case - expected 0x07C5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
}


void testdg_packthreebytevex()
{
    Bufferhandle BHarrayhead;
    UINT64 x;
    
    dg_initpbharrayhead(&BHarrayhead);
    
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_packthreebytevex\n");
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        1, // rexdotb, // 0 or 1   gets inverted  bit 13
        1, // rexdotx, // 0 or 1   gets inverted  bit 14
        1, // rexdotr, // 0 or 1   gets inverted  bit 15
        0, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        0, // vectorlength, // 0 = 128, 1 = 256  bit 18
        15, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x0000C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 1 1 1 0 0 15 0 case - expected 0x0000C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        3, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        1, // rexdotb, // 0 or 1   gets inverted  bit 13
        1, // rexdotx, // 0 or 1   gets inverted  bit 14
        1, // rexdotr, // 0 or 1   gets inverted  bit 15
        0, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        0, // vectorlength, // 0 = 128, 1 = 256  bit 18
        15, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x0003C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 3 1 1 1 0 0 15 0 case - expected 0x0003C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        0, // rexdotb, // 0 or 1   gets inverted  bit 13
        1, // rexdotx, // 0 or 1   gets inverted  bit 14
        1, // rexdotr, // 0 or 1   gets inverted  bit 15
        0, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        0, // vectorlength, // 0 = 128, 1 = 256  bit 18
        15, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x0020C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 0 1 1 0 0 15 0 case - expected 0x0020C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        0, // rexdotb, // 0 or 1   gets inverted  bit 13
        0, // rexdotx, // 0 or 1   gets inverted  bit 14
        1, // rexdotr, // 0 or 1   gets inverted  bit 15
        0, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        0, // vectorlength, // 0 = 128, 1 = 256  bit 18
        15, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x0060C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 0 0 1 0 0 15 0 case - expected 0x0060C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        0, // rexdotb, // 0 or 1   gets inverted  bit 13
        0, // rexdotx, // 0 or 1   gets inverted  bit 14
        0, // rexdotr, // 0 or 1   gets inverted  bit 15
        0, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        0, // vectorlength, // 0 = 128, 1 = 256  bit 18
        15, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x00E0C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 0 0 0 0 0 15 0 case - expected 0x00E0C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        0, // rexdotb, // 0 or 1   gets inverted  bit 13
        0, // rexdotx, // 0 or 1   gets inverted  bit 14
        0, // rexdotr, // 0 or 1   gets inverted  bit 15
        3, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        0, // vectorlength, // 0 = 128, 1 = 256  bit 18
        15, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x03E0C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 0 0 0 3 0 15 0 case - expected 0x03E0C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        0, // rexdotb, // 0 or 1   gets inverted  bit 13
        0, // rexdotx, // 0 or 1   gets inverted  bit 14
        0, // rexdotr, // 0 or 1   gets inverted  bit 15
        3, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        1, // vectorlength, // 0 = 128, 1 = 256  bit 18
        15, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x07E0C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 0 0 0 3 1 15 0 case - expected 0x07E0C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        0, // rexdotb, // 0 or 1   gets inverted  bit 13
        0, // rexdotx, // 0 or 1   gets inverted  bit 14
        0, // rexdotr, // 0 or 1   gets inverted  bit 15
        3, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        1, // vectorlength, // 0 = 128, 1 = 256  bit 18
        0, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        0); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0x7FE0C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 0 0 0 3 1 0 0 case - expected 0x7FE0C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_packthreebytevex (
        0, // leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A  bits 8 - 12
        0, // rexdotb, // 0 or 1   gets inverted  bit 13
        0, // rexdotx, // 0 or 1   gets inverted  bit 14
        0, // rexdotr, // 0 or 1   gets inverted  bit 15
        3, // simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2  bits 16 - 17
        1, // vectorlength, // 0 = 128, 1 = 256  bit 18
        0, // secondsourcereg, // 0-15  gets inverted  bits 19 - 22
        1); // rexdotw);         // 0 or 1 comes from opcode sequence apparently bit 23
    
    if (x != 0xFFE0C4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_packthreebytevex success 0 0 0 0 3 1 0 1 case - expected 0xFFE0C4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}
/*
void dg_compilevex ( // need to add way to force promotion to 3 byte vex...
    Bufferhandle* pBHarrayhead,
    dg_Sibformatter* psf,
    UINT64 addresssize,
    UINT64 simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
    UINT64 leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A
    UINT64 rexdotw, // 0x48 comes from opcode I think
    UINT64 usethreebytevex) // not zero means use three byte vex
*/
    
void testdg_compilevex()
{
    Bufferhandle BHarrayhead;
    
    dg_initpbharrayhead(&BHarrayhead);
    
    Bufferhandle* pBH = NULL;
    
    const char* pError = NULL;
    
    struct dg_Sibformatter mysibformatter;
    
    UINT64 mycurrentcompilebuffer;
    UINT64 mystartoffset;
    UINT64 x;
    
    unsigned char* pccbuf;
    UINT64* pccbuflength;
    
    unsigned char c;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_compilevex\n");
    
    
    // two byte success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - could not get current compile buffer\n");
        return;
    }
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - could not get current compile buffer's length\n");
        return;
    }
    
    dg_initSibformatter(&mysibformatter);
    
    mysibformatter.basereg = dg_xmm0;
    mysibformatter.size = 16;
    mysibformatter.targetreg = dg_xmm1;
    mysibformatter.memmode = dg_memmodexmmreg;
    // secondsourcereg is left at 0 which is what it's supposed to be if unused...
    
    dg_formatpsf (
        &BHarrayhead,
        &mysibformatter);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - got an error formatting the sib\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
        
    dg_compilevex (
        &BHarrayhead,
        &mysibformatter,
        8, // addresssize,
        3, // simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        1, // leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A // 1 for 2 byte vex
        0, // rexdotw,
        0); // usethreebytevex);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - got an error compiling vex\n");
        return;
    }
    
    pccbuf = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pccbuflength);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - got an error getting a pointer to the current compile buffer.\n");
        return;
    }
    
    x = ((*pccbuflength) - mystartoffset);
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - expected vex length 2, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset] != 0xC5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - 1st byte expected 0xC5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+1] != 0xFB)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex two byte vex success case - 2nd byte expected 0xFB, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // three byte forced success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - could not get current compile buffer\n");
        return;
    }
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - could not get current compile buffer's length\n");
        return;
    }
    
    dg_initSibformatter(&mysibformatter);
    
    mysibformatter.basereg = dg_xmm0;
    mysibformatter.size = 16;
    mysibformatter.targetreg = dg_xmm1;
    mysibformatter.memmode = dg_memmodexmmreg;
    // secondsourcereg is left at 0 which is what it's supposed to be if unused...
    
    dg_formatpsf (
        &BHarrayhead,
        &mysibformatter);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - got an error formatting the sib\n");
        return;
    }
        
    dg_compilevex (
        &BHarrayhead,
        &mysibformatter,
        8, // addresssize,
        3, // simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        1, // leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A // 1 for 2 byte vex
        0, // rexdotw,
        1); // usethreebytevex);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - got an error compiling vex\n");
        return;
    }
    
    pccbuf = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pccbuflength);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - got an error getting a pointer to the current compile buffer.\n");
        return;
    }
    
    x = (*pccbuflength) - mystartoffset;
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - expected vex length 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset] != 0xC4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - 1st byte expected 0xC5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+1] != 0xE1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - 2nd byte expected 0xE1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+2] != 0x7B)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex forced success case - 3rd byte expected 0x7B, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // three byte w = 1 success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - could not get current compile buffer\n");
        return;
    }
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - could not get current compile buffer's length\n");
        return;
    }
    
    dg_initSibformatter(&mysibformatter);
    
    mysibformatter.basereg = dg_xmm0;
    mysibformatter.size = 16;
    mysibformatter.targetreg = dg_xmm1;
    mysibformatter.memmode = dg_memmodexmmreg;
    // secondsourcereg is left at 0 which is what it's supposed to be if unused...
    
    dg_formatpsf (
        &BHarrayhead,
        &mysibformatter);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - got an error formatting the sib\n");
        return;
    }
        
    dg_compilevex (
        &BHarrayhead,
        &mysibformatter,
        8, // addresssize,
        3, // simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        1, // leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A // 1 for 2 byte vex
        1, // rexdotw,
        0); // usethreebytevex);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - got an error compiling vex\n");
        return;
    }
    
    pccbuf = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pccbuflength);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - got an error getting a pointer to the current compile buffer.\n");
        return;
    }
    
    x = (*pccbuflength) - mystartoffset;
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - expected vex length 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset] != 0xC4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - 1st byte expected 0xC5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+1] != 0xE1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - 2nd byte expected 0xE1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+2] != 0xFB)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex w = 1 success case - 3rd byte expected 0xFB, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // three byte leading opcode not 0x0f success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - could not get current compile buffer\n");
        return;
    }
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - could not get current compile buffer's length\n");
        return;
    }
    
    dg_initSibformatter(&mysibformatter);
    
    mysibformatter.basereg = dg_xmm0;
    mysibformatter.size = 16;
    mysibformatter.targetreg = dg_xmm1;
    mysibformatter.memmode = dg_memmodexmmreg;
    // secondsourcereg is left at 0 which is what it's supposed to be if unused...
    
    dg_formatpsf (
        &BHarrayhead,
        &mysibformatter);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - got an error formatting the sib\n");
        return;
    }
        
    dg_compilevex (
        &BHarrayhead,
        &mysibformatter,
        8, // addresssize,
        3, // simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        3, // leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A // 1 for 2 byte vex
        0, // rexdotw,
        0); // usethreebytevex);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - got an error compiling vex\n");
        return;
    }
    
    pccbuf = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pccbuflength);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - got an error getting a pointer to the current compile buffer.\n");
        return;
    }
    
    x = (*pccbuflength) - mystartoffset;
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - expected vex length 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset] != 0xC4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - 1st byte expected 0xC5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+1] != 0xE3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - 2nd byte expected 0xE3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+2] != 0x7B)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex leading opcode not 0x0f success case - 3rd byte expected 0x7B, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // three byte b not 0 success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - could not get current compile buffer\n");
        return;
    }
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - could not get current compile buffer's length\n");
        return;
    }
    
    dg_initSibformatter(&mysibformatter);
    
    mysibformatter.basereg = dg_xmm8;
    mysibformatter.size = 16;
    mysibformatter.targetreg = dg_xmm1;
    mysibformatter.memmode = dg_memmodexmmreg;
    // secondsourcereg is left at 0 which is what it's supposed to be if unused...
    
    dg_formatpsf (
        &BHarrayhead,
        &mysibformatter);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - got an error formatting the sib\n");
        return;
    }
        
    dg_compilevex (
        &BHarrayhead,
        &mysibformatter,
        8, // addresssize,
        3, // simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        1, // leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A // 1 for 2 byte vex
        0, // rexdotw,
        0); // usethreebytevex);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - got an error compiling vex\n");
        return;
    }
    
    pccbuf = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pccbuflength);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - got an error getting a pointer to the current compile buffer.\n");
        return;
    }
    
    x = (*pccbuflength) - mystartoffset;
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - expected vex length 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset] != 0xC4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - 1st byte expected 0xC5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset] != 0xC4);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+1] != 0xC1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - 2nd byte expected 0xC1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+2] != 0x7B)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex b not 0 success case - 3rd byte expected 0x7B, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // three byte x = 1 success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - could not get current compile buffer\n");
        return;
    }
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - could not get current compile buffer's length\n");
        return;
    }
    
    dg_initSibformatter(&mysibformatter);
    
    mysibformatter.basereg = dg_rax;
    mysibformatter.indexreg = dg_r8;
    mysibformatter.size = 16;
    mysibformatter.targetreg = dg_xmm1;
    // scale, displacementsize, displacement all default
    mysibformatter.memmode = dg_memmodesib;
    // secondsourcereg is left at 0 which is what it's supposed to be if unused...
    
    dg_formatpsf (
        &BHarrayhead,
        &mysibformatter);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - got an error formatting the sib\n");
        return;
    }
        
    dg_compilevex (
        &BHarrayhead,
        &mysibformatter,
        8, // addresssize,
        3, // simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        1, // leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A // 1 for 2 byte vex
        0, // rexdotw,
        0); // usethreebytevex);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - got an error compiling vex\n");
        return;
    }
    
    pccbuf = dg_getpbuffer(
        &BHarrayhead,
        mycurrentcompilebuffer,
        &pccbuflength);
        
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - got an error getting a pointer to the current compile buffer.\n");
        return;
    }
    
    x = (*pccbuflength) - mystartoffset;
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - expected vex length 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset] != 0xC4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - 1st byte expected 0xC5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+1] != 0xA1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - 2nd byte expected 0xA1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pccbuf[mystartoffset+2] != 0x7B)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing dg_compilevex three byte vex x = 1 success case - 3rd byte expected 0x7B, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pccbuf[mystartoffset+2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


/*
unsigned char* dg_search (
	unsigned char* caddr1, // target string to search
	UINT32 u1, // length of target string 
	unsigned char* caddr2, // string to search for in target string
	UINT32 u2,             // length of string to search for 
    unsigned char** pcaddrout) // pointer to found string or pointer to null 
    
returns dg_success on success
returns dg_badmemoryerror if memory at strings is not part of current process
*/

/*
void testcompiles()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.nextunusedbyte = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;
	
//	Bufferhandle* pBH = NULL;
	
//	const char* pError = NULL;
	UINT32 mycurrentcompilebuffer = 0;
	UINT32 mystartoffset = 0;
	UINT32 x = 0;
	INT32 myflag=5;
	
	unsigned char mysourcestring[12] = "hello there";
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing compiles - compile copy of a string and push ptr and length of that string to the data stack\n");
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to push pointer to and length of a copy of a string to the data stack
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not compile init locals\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, UINT32(mysourcestring));
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not push address of source string to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 11);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not push length of source string to data stack\n");
		return;
	}
	
	dg_forthcompiles(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not do dg_forthcompiles got errors:\n");
		dg_forthdoterrors(&BHarrayhead);
		return;
	}	
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - top number on data stack after executed compiled string code incorrect, length not same as source string\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x == (UINT64)mysourcestring)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - 2nd number on data stack after executed compiled string code incorrect, address of copy was same as source string\n");
		return;
	}
	
	if (dg_comparebytes(mysourcestring, 11, (unsigned char*)x, 11, &myflag) != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - compare of source string and copy failed\n");
		return;
	}
	
	if (myflag != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing compiles success case - string at reported address or copy not same as source string\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}
*/



