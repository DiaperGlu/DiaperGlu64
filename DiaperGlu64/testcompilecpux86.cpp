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

#include "diapergluforth.h"
#include "testdglu.h"

void testdg_forthregscurly()
{
    Bufferhandle BHarrayhead;
    UINT64 stringlength;
    const char* perror;
    UINT64 bufferid;
    UINT64 x;
    UINT64 localregindex;
    UINT64 localreg;

    Bufferhandle* pBH;

    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists(&BHarrayhead);
    dg_initwordlists(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthregscurly\n");
 
    // success case

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        0x0);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64\n");
        return;
    }

    const char pteststring[] = "X86-WORDLIST >SEARCH-ORDER REGS< moo > moo\r";

    stringlength = largestunsignedint;
    perror = dg_scanforbyte (
        (void*)pteststring,
        &stringlength,
        0);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_scanforbyte, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        return;
    }

    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000, // growby,
        0x1000, // maxsize,
        (unsigned char*)pteststring,
        stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_stonewbuffer\n");
        return;
    }

    dg_evaluatebuffer (
        &BHarrayhead, 
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_evaluatebuffer\n");
        return;
    }

    // first allocatable reg should be on the data stack...
    x = dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_popdatastack\n");
        return;
    }

    localregindex = dg_localsintregallocationorder[0];
    localreg = dg_localsregs[localregindex];
    
    if (x != localreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthregscurly success case  - got wrong allocated reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, localreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    const char pteststring2[] = "REGS< moo2 > moo2\r";

    stringlength = largestunsignedint;
    perror = dg_scanforbyte (
        (void*)pteststring2,
        &stringlength,
        0);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_scanforbyte 2nd time, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        return;
    }

    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000, // growby,
        0x1000, // maxsize,
        (unsigned char*)pteststring2,
        stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_stonewbuffer 2nd time\n");
        return;
    }

    dg_evaluatebuffer (
        &BHarrayhead, 
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_evaluatebuffer 2nd time\n");
        return;
    }

    // first allocatable reg should be on the data stack...
    x = dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_popdatastack 2nd time\n");
        return;
    }

    localregindex = dg_localsintregallocationorder[1];
    localreg = dg_localsregs[localregindex];
    
    if (x != localreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthregscurly 2nd time success case  - got wrong allocated reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, localreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    const char pteststring3[] = "REGS< moo3 > moo3\r";

    stringlength = largestunsignedint;
    perror = dg_scanforbyte (
        (void*)pteststring3,
        &stringlength,
        0);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_scanforbyte 3rd time, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        return;
    }

    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000, // growby,
        0x1000, // maxsize,
        (unsigned char*)pteststring3,
        stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_stonewbuffer 3rd time\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- stringlength = ");
        dg_writestdoutuint64tohex(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_evaluatebuffer (
        &BHarrayhead, 
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_evaluatebuffer 3rd time\n");
        return;
    }

    // first allocatable reg should be on the data stack...
    x = dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_popdatastack 3rd time\n");
        return;
    }

    localregindex = dg_localsintregallocationorder[2];
    localreg = dg_localsregs[localregindex];
    
    if (x != localreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthregscurly 3rd time success case  - got wrong allocated reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, localreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // no regs available case... should get an error
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        largestunsignedint);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64\n");
        return;
    }

    const char pteststring4[] = "REGS< moo4 > moo4";

    stringlength = largestunsignedint;
    perror = dg_scanforbyte (
        (void*)pteststring4,
        &stringlength,
        0);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_scanforbyte 4th time, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        return;
    }

    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000, // growby,
        0x1000, // maxsize,
        (unsigned char*)pteststring4,
        stringlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_stonewbuffer 4th time\n");
        return;
    }

    dg_evaluatebuffer (
        &BHarrayhead, 
        bufferid);

    // should get error... 
    if (dg_geterrorcount(&BHarrayhead) == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got no errors doing dg_evaluatebuffer 4th time\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);
}

void testdg_usenextunusedlocalsintreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    UINT64 x;
    UINT64 usedregindex;
    UINT64 usedregmask;
    UINT64 usedreg;
    UINT64 localsregsused;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_usenextunusedlocalsintreg\n");
    
    // uses only dg_localsregsused
    // success case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        0x0);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64\n");
        return;
    }

    x = dg_usenextunusedlocalsintreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsintreg\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64\n");
        return;
    }

    usedregindex = dg_localsintregallocationorder[0];

    usedregmask = dg_twototheu(usedregindex);

    usedreg = dg_localsregs[usedregindex];
    
    if (localsregsused != usedregmask)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != usedreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // 2nd allocation
    x = dg_usenextunusedlocalsintreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsintreg 2nd time\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64 2nd time\n");
        return;
    }

    usedregindex = dg_localsintregallocationorder[1];

    usedregmask = dg_twototheu(usedregindex) | dg_twototheu(dg_localsintregallocationorder[0]);

    usedreg = dg_localsregs[usedregindex];
    
    if (localsregsused != usedregmask)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg 2nd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != usedreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg 2nd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // 3rd allocation
    x = dg_usenextunusedlocalsintreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsintreg 3rd time\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64 3rd time\n");
        return;
    }

    usedregindex = dg_localsintregallocationorder[2];

    usedregmask = dg_twototheu(usedregindex) | dg_twototheu(dg_localsintregallocationorder[1]) | dg_twototheu(dg_localsintregallocationorder[0]);

    usedreg = dg_localsregs[usedregindex];
    
    if (localsregsused != usedregmask)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg 3rd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != usedreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg 3rd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // none available
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        (UINT64)-1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64 none available\n");
        return;
    }

    x = dg_usenextunusedlocalsintreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsintreg non available\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64 non available\n");
        return;
    }
    
    if (localsregsused != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg none available success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != dg_noreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsintreg none available success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, dg_noreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}

void testdg_usenextunusedlocalsfloatreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    UINT64 x;
    UINT64 usedregindex;
    UINT64 usedregmask;
    UINT64 usedreg;
    UINT64 localsregsused;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_usenextunusedlocalsfloatreg\n");
    
    // uses only dg_localsregsused
    // success case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        0x0);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64\n");
        return;
    }

    x = dg_usenextunusedlocalsfloatreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsintreg\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64\n");
        return;
    }

    usedregindex = dg_localsfloatregallocationorder[0];

    usedregmask = dg_twototheu(usedregindex);

    usedreg = dg_localsregs[usedregindex];
    
    if (localsregsused != usedregmask)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != usedreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // 2nd allocation
    x = dg_usenextunusedlocalsfloatreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsfloatreg 2nd time\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64 2nd time\n");
        return;
    }

    usedregindex = dg_localsfloatregallocationorder[1];

    usedregmask = dg_twototheu(usedregindex) | dg_twototheu(dg_localsfloatregallocationorder[0]);

    usedreg = dg_localsregs[usedregindex];
    
    if (localsregsused != usedregmask)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg 2nd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != usedreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg 2nd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // 3rd allocation
    x = dg_usenextunusedlocalsfloatreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsfloatreg 3rd time\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64 3rd time\n");
        return;
    }

    usedregindex = dg_localsfloatregallocationorder[2];

    usedregmask = dg_twototheu(usedregindex) | dg_twototheu(dg_localsfloatregallocationorder[1]) | dg_twototheu(dg_localsfloatregallocationorder[0]);

    usedreg = dg_localsregs[usedregindex];
    
    if (localsregsused != usedregmask)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg 3rd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != usedreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg 3rd allocation success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // none available
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        (UINT64)-1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64 none available\n");
        return;
    }

    x = dg_usenextunusedlocalsfloatreg(&BHarrayhead);
    // localsregsused gets the index bit set from the used reg
    // the returned value is the reg...

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_usenextunusedlocalsfloatreg non available\n");
        return;
    }

    localsregsused = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64 non available\n");
        return;
    }
    
    if (localsregsused != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg none available success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, usedregmask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, localsregsused);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (x != dg_noreg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_usenextunusedlocalsfloatreg none available success case  - got wrong used reg, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, dg_noreg);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"  got, ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}

void testdg_forthallrmaskunuse()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthallrmaskunuse\n");
    
    // success case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        0x12345678);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64\n");
        return;
    }

    dg_forthallrmaskunuse (&BHarrayhead); 

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_forthunuseallregs\n");
        return;
    }
   
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthallrmaskunuse success case  - got wrong result, expected 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}

void testdg_marklocalsregasused()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_marklocalsregasused\n");
    
    // success bit 0 case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        0);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_putbufferuint64\n");
        return;
    }

    dg_marklocalsregasused (
        &BHarrayhead,
        0); // localsregindex); 

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_marklocalsregasused\n");
        return;
    }
   
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64\n");
        return;
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_marklocalsregasused bit 0 success case  - got wrong result, expected 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // success adding bit 1 case
    dg_marklocalsregasused (
        &BHarrayhead,
        1); // localsregindex);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_marklocalsregasused\n");
        return;
    }
   
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64\n");
        return;
    }

    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_marklocalsregasused adding bit 1 success case  - got wrong result, expected 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // success adding bit 3 case
    dg_marklocalsregasused (
        &BHarrayhead,
        3); // localsregindex); 

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_marklocalsregasused\n");
        return;
    }
   
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" -- got error doing dg_getbufferuint64\n");
        return;
    }
    
    if (x != 0x0b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_marklocalsregasused adding bit 3 success case  - got wrong result, expected 0x0b, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}

void testdg_paramregsindextolocalsregindex()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 localsregindex;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_paramregsindextolocalsregindex\n");
    
    // unknown type case
    localsregindex = dg_paramregsindextolocalsregindex (
        0,  // paramregsindex,
        2); // paramregstype);   
    
    if (localsregindex != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex unknown type success case  - got wrong index\n");
        return;
    }

    // unknown type case
    localsregindex = dg_paramregsindextolocalsregindex (
        0,  // paramregsindex,
        2); // paramregstype);   
    
    if (localsregindex != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex unknown type success case  - got wrong index\n");
        return;
    }

    // int reg 0 case
    localsregindex = dg_paramregsindextolocalsregindex (
        0,  // paramregsindex,
        0); // paramregstype);   
    
    if (localsregindex != dg_paramintregslocalsindex[0])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex int reg 0 success case  - got wrong index\n");
        return;
    }

    // int reg 1 case
    localsregindex = dg_paramregsindextolocalsregindex (
        1,  // paramregsindex,
        0); // paramregstype);   
    
    if (localsregindex != dg_paramintregslocalsindex[1])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex int reg 1 success case  - got wrong index\n");
        return;
    }

    // int reg 2 case
    localsregindex = dg_paramregsindextolocalsregindex (
        2,  // paramregsindex,
        0); // paramregstype);   
    
    if (localsregindex != dg_paramintregslocalsindex[2])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex int reg 2 success case  - got wrong index\n");
        return;
    }

    // int reg 3 case
    localsregindex = dg_paramregsindextolocalsregindex (
        3,  // paramregsindex,
        0); // paramregstype);   
    
    if (localsregindex != dg_paramintregslocalsindex[3])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex int reg 3 success case  - got wrong index\n");
        return;
    }

    // int reg 4 case
    localsregindex = dg_paramregsindextolocalsregindex (
        4,  // paramregsindex,
        0); // paramregstype);   

    if (dg_numberofparamintregs < 5)
    {    
        if (localsregindex != largestunsignedint)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex int reg 4 success case  - got wrong index, got ");
            dg_writestdoutuint64tohex(&BHarrayhead, localsregindex);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
            return;
        }
    }
    else
    {
        if (localsregindex != dg_paramintregslocalsindex[4])
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex int reg 4 success case  - got wrong index, expected ");
            dg_writestdoutuint64tohex(&BHarrayhead, dg_paramintregslocalsindex[4]);
            dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
            dg_writestdoutuint64tohex(&BHarrayhead, localsregindex);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
            return;
        }
    }

    // float reg 0 case
    localsregindex = dg_paramregsindextolocalsregindex (
        0,  // paramregsindex,
        1); // paramregstype);   
    
    if (localsregindex != dg_paramfloatregslocalsindex[0])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex float reg 0 success case  - got wrong index\n");
        return;
    }

    // float reg 1 case
    localsregindex = dg_paramregsindextolocalsregindex (
        1,  // paramregsindex,
        1); // paramregstype);   
    
    if (localsregindex != dg_paramfloatregslocalsindex[1])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex float reg 1 success case  - got wrong index\n");
        return;
    }

    // float reg 2 case
    localsregindex = dg_paramregsindextolocalsregindex (
        2,  // paramregsindex,
        1); // paramregstype);   
    
    if (localsregindex != dg_paramfloatregslocalsindex[2])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex float reg 2 success case  - got wrong index\n");
        return;
    }

    // float reg 3 case
    localsregindex = dg_paramregsindextolocalsregindex (
        3,  // paramregsindex,
        1); // paramregstype);   
    
    if (localsregindex != dg_paramfloatregslocalsindex[3])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex float reg 3 success case  - got wrong index\n");
        return;
    }

    // float reg 4 case
    localsregindex = dg_paramregsindextolocalsregindex (
        4,  // paramregsindex,
        1); // paramregstype);
   
    if (dg_numberofparamfloatregs < 5)
    {
        if (localsregindex != largestunsignedint)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex float reg 4 success case  - got wrong index\n");
            return;
        }
    }
    else
    {
        if (localsregindex != dg_paramfloatregslocalsindex[4])
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_paramregsindextolocalsregindex float reg 4 success case  - got wrong index\n");
            return;
        }
    }
}

void testdg_regtolocalsregindex()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 localsregindex;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_regtolocalsregindex\n");
    
    // dg_rax case
    localsregindex = dg_regtolocalsregindex (dg_rax);    
    
    if (localsregindex != dg_localsraxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rax success case  - got wrong index\n");
        return;
    }

    // dg_rbx case
    localsregindex = dg_regtolocalsregindex (dg_rbx);    
    
    if (localsregindex != dg_localsrbxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rbx success case  - got wrong index\n");
        return;
    }

    // dg_rcx case
    localsregindex = dg_regtolocalsregindex (dg_rcx);    
    
    if (localsregindex != dg_localsrcxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rcx success case  - got wrong index\n");
        return;
    }

    // dg_rdx case
    localsregindex = dg_regtolocalsregindex (dg_rdx);    
    
    if (localsregindex != dg_localsrdxindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rdx success case  - got wrong index\n");
        return;
    }

    // dg_rsi case
    localsregindex = dg_regtolocalsregindex (dg_rsi);    
    
    if (localsregindex != dg_localsrsiindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rsi success case  - got wrong index\n");
        return;
    }

    // dg_rdi case
    localsregindex = dg_regtolocalsregindex (dg_rdi);    
    
    if (localsregindex != dg_localsrdiindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rdi success case  - got wrong index\n");
        return;
    }

    // dg_rbp case
    localsregindex = dg_regtolocalsregindex (dg_rbp);    
    
    if (localsregindex != dg_localsrbpindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rbp success case  - got wrong index\n");
        return;
    }

    // dg_rsp case
    localsregindex = dg_regtolocalsregindex (dg_rsp);    
    
    if (localsregindex != dg_localsrspindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rsp success case  - got wrong index\n");
        return;
    }

    // dg_xmm0 case
    localsregindex = dg_regtolocalsregindex (dg_xmm0);    
    
    if (localsregindex != dg_localsxmm0index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm0 success case  - got wrong index\n");
        return;
    }

    // dg_xmm1 case
    localsregindex = dg_regtolocalsregindex (dg_xmm1);    
    
    if (localsregindex != dg_localsxmm1index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm1 success case  - got wrong index\n");
        return;
    }

    // dg_xmm2 case
    localsregindex = dg_regtolocalsregindex (dg_xmm2);    
    
    if (localsregindex != dg_localsxmm2index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm2 success case  - got wrong index\n");
        return;
    }

    // dg_xmm3 case
    localsregindex = dg_regtolocalsregindex (dg_xmm3);    
    
    if (localsregindex != dg_localsxmm3index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm3 success case  - got wrong index\n");
        return;
    }

    // dg_xmm4 case
    localsregindex = dg_regtolocalsregindex (dg_xmm4);    
    
    if (localsregindex != dg_localsxmm4index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm4 success case  - got wrong index\n");
        return;
    }

    // dg_xmm5 case
    localsregindex = dg_regtolocalsregindex (dg_xmm5);    
    
    if (localsregindex != dg_localsxmm5index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm5 success case  - got wrong index\n");
        return;
    }

    // dg_xmm6 case
    localsregindex = dg_regtolocalsregindex (dg_xmm6);    
    
    if (localsregindex != dg_localsxmm6index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm6 success case  - got wrong index\n");
        return;
    }

    // dg_xmm7 case
    localsregindex = dg_regtolocalsregindex (dg_xmm7);    
    
    if (localsregindex != dg_localsxmm7index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm7 success case  - got wrong index\n");
        return;
    }
    
    // dg_xmm8 case
    localsregindex = dg_regtolocalsregindex (dg_xmm8);    
    
    if (localsregindex != dg_localsxmm8index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm8 success case  - got wrong index\n");
        return;
    }

    // dg_xmm9 case
    localsregindex = dg_regtolocalsregindex (dg_xmm9);    
    
    if (localsregindex != dg_localsxmm9index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm9 success case  - got wrong index\n");
        return;
    }

    // dg_xmm10 case
    localsregindex = dg_regtolocalsregindex (dg_xmm10);    
    
    if (localsregindex != dg_localsxmm10index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm10 success case  - got wrong index\n");
        return;
    }

    // dg_xmm11 case
    localsregindex = dg_regtolocalsregindex (dg_xmm11);    
    
    if (localsregindex != dg_localsxmm11index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xm11 success case  - got wrong index\n");
        return;
    }

    // dg_xmm12 case
    localsregindex = dg_regtolocalsregindex (dg_xmm12);    
    
    if (localsregindex != dg_localsxmm12index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm12 success case  - got wrong index\n");
        return;
    }

    // dg_xmm13 case
    localsregindex = dg_regtolocalsregindex (dg_xmm13);    
    
    if (localsregindex != dg_localsxmm13index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm13 success case  - got wrong index\n");
        return;
    }

    // dg_xmm14 case
    localsregindex = dg_regtolocalsregindex (dg_xmm14);    
    
    if (localsregindex != dg_localsxmm14index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xmm14 success case  - got wrong index\n");
        return;
    }

    // dg_xmm15 case
    localsregindex = dg_regtolocalsregindex (dg_xmm15);    
    
    if (localsregindex != dg_localsxmm15index)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_xm15 success case  - got wrong index\n");
        return;
    }

    // dg_noreg case
    localsregindex = dg_regtolocalsregindex (dg_noreg);    
    
    if (largestunsignedint != localsregindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_noreg success case  - got wrong index\n");
        return;
    }

    // dg_rip case
    localsregindex = dg_regtolocalsregindex (dg_rip);    
    
    if (largestunsignedint != localsregindex)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_regtolocalsregindex dg_rip success case  - got wrong index\n");
        return;
    }
}

void testdg_localsregindextoreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 reg;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_localsregindextoreg\n");
    
    // dg_rax case
    reg = dg_localsregindextoreg (dg_localsraxindex);    
    
    if (dg_rax != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rax success case  - got wrong reg\n");
        return;
    }

    // dg_rbx case
    reg = dg_localsregindextoreg (dg_localsrbxindex);    
    
    if (dg_rbx != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rbx success case  - got wrong reg\n");
        return;
    }

    // dg_rcx case
    reg = dg_localsregindextoreg (dg_localsrcxindex);    
    
    if (dg_rcx != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rcx success case  - got wrong reg\n");
        return;
    }

    // dg_rdx case
    reg = dg_localsregindextoreg (dg_localsrdxindex);    
    
    if (dg_rdx != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rdx success case  - got wrong reg\n");
        return;
    }

    // dg_rsi case
    reg = dg_localsregindextoreg (dg_localsrsiindex);    
    
    if (dg_rsi != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rsi success case  - got wrong reg\n");
        return;
    }

    // dg_rdi case
    reg = dg_localsregindextoreg (dg_localsrdiindex);    
    
    if (dg_rdi != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rdi success case  - got wrong reg\n");
        return;
    }

    // dg_rbp case
    reg = dg_localsregindextoreg (dg_localsrbpindex);    
    
    if (dg_rbp != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rbp success case  - got wrong reg\n");
        return;
    }

    // dg_rsp case
    reg = dg_localsregindextoreg (dg_localsrspindex);    
    
    if (dg_rsp != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_rsp success case  - got wrong reg\n");
        return;
    }

    // dg_xmm0 case
    reg = dg_localsregindextoreg (dg_localsxmm0index);    
    
    if (dg_xmm0 != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_xmm0 success case  - got wrong reg\n");
        return;
    }

    // dg_xmm15 case
    reg = dg_localsregindextoreg (dg_localsxmm15index);    
    
    if (dg_xmm15 != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg dg_xmm15 success case  - got wrong reg\n");
        return;
    }

    // bad index case
    reg = dg_localsregindextoreg (dg_localsxmm15index + 1);    
    
    if (dg_noreg != reg)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_localsregindextoreg bad index success case  - got wrong reg\n");
        return;
    }
}

void testdg_bumpdisplacementsizeifneeded()
{
    dg_Sibformatter mysf;
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_bumpdisplacementsizeifneeded\n");
    
    // displacement 0 case
    dg_initSibformatter(&mysf);
    
    dg_bumpdisplacementsizeifneeded (&mysf);
    
    if (mysf.displacementsize != dg_sizenone)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_bumpdisplacementsizeifneeded displacement 0 success case  - displacement was changed\n");
        return;
    }
    
    // displacement 1 case
    dg_initSibformatter(&mysf);
    
    mysf.displacement = 1;
    
    dg_bumpdisplacementsizeifneeded (&mysf);
    
    if (mysf.displacementsize != dg_sizebyte)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_bumpdisplacementsizeifneeded displacement 1 success case  - displacement was not promoted to byte\n");
        return;
    }
    
    // displacement -1 case
    dg_initSibformatter(&mysf);
    
    mysf.displacement = -1;
    
    dg_bumpdisplacementsizeifneeded (&mysf);
    
    if (mysf.displacementsize != dg_sizebyte)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_bumpdisplacementsizeifneeded displacement -1 success case  - displacement was not promoted to byte\n");
        return;
    }
    
    // displacement 0x7f case
    dg_initSibformatter(&mysf);
    
    mysf.displacement = 0x7f;
    
    dg_bumpdisplacementsizeifneeded (&mysf);
    
    if (mysf.displacementsize != dg_sizebyte)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_bumpdisplacementsizeifneeded displacement 0x7f success case  - displacement was not promoted to byte\n");
        return;
    }
    
    // displacement -0x80 case
    dg_initSibformatter(&mysf);
    
    mysf.displacement = -0x80;
    
    dg_bumpdisplacementsizeifneeded (&mysf);
    
    if (mysf.displacementsize != dg_sizebyte)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_bumpdisplacementsizeifneeded displacement -0x80 success case  - displacement was not promoted to byte\n");
        return;
    }
    
    // displacement 0x80 case
    dg_initSibformatter(&mysf);
    
    mysf.displacement = 0x80;
    
    dg_bumpdisplacementsizeifneeded (&mysf);
    
    if (mysf.displacementsize != dg_sizedword)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_bumpdisplacementsizeifneeded displacement 0x80 success case  - displacement was not promoted to 32 bits\n");
        return;
    }
    
    // displacement -0x81 case
    dg_initSibformatter(&mysf);
    
    mysf.displacement = -0x81;
    
    dg_bumpdisplacementsizeifneeded (&mysf);
    
    if (mysf.displacementsize != dg_sizedword)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_bumpdisplacementsizeifneeded displacement -0x81 success case  - displacement was not promoted to 32 bits\n");
        return;
    }
}

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

void testdg_compilemovfregtofreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    FLOAT64 x;

    FLOAT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovfregtofreg\n");

    // [rsp]->xmm0 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg [rsp]->xmm0 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg [rsp]->xmm0 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg [rsp]->xmm0 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg [rsp]->xmm0 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg [rsp]->xmm0 success case - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // xmm1->xmm0 success case

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm0);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // xmm1->xmm0 success case b

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case b - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm0);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case b - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case b - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // xmm1->xmm0 success case c (test src and dest aren't backwards...)

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case c - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm0);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case c - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm1->xmm0 success case c - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // xmm8->xmm0 success case

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm0);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }    
    

    // xmm8->xmm0 success case b

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case b - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm0);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case b - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm8->xmm0 success case b - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // xmm0->xmm8 success case

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm0->xmm8 success case - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm0->xmm8 success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm0,
        dg_xmm8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm0);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm0->xmm8 success case - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm0->xmm8 success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm0->xmm8 success case - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // xmm9->xmm8 success case

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm9->xmm8 success case - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm9->xmm8 success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2983987439,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm9);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0,
        dg_rax);

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm9,
        dg_xmm8);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm9);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm0);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm9->xmm8 success case - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm9->xmm8 success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (*((UINT64*)(&x)) != 0x2983987439)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtofreg xmm9->xmm8 success case - return not 0x2983987439, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&x)));
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilesubn8fromrsp\n");

    // subtract 0x20 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp 0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp 0x20 success case  - could not get current compile buffer's length\n");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp 0x20 success case  - error compiling test routine\n");
        return;
    }
    
    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp 0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp subtract 0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp -0x10 success case  - could not get current compile buffer's length\n");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp -0x10 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp -0x10 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubn8fromrsp subtract -0x10 success case - return not 0x10, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilesubnfromrsp()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 mybeforeoffset = 0;
    UINT64 myafteroffset = 0;
    UINT64 x;

    UINT64 (*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilesubnfromrsp\n");

    // subtract 0x20 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    mybeforeoffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case  - could not get current compile buffer's length 2\n");
        return;
    }

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x20);

    myafteroffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case  - could not get current compile buffer's length 3\n");
        return;
    }

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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case  - error compiling test routine\n");
        return;
    }
    
    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (4 != (myafteroffset - mybeforeoffset))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x20 success case - return not 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (myafteroffset - mybeforeoffset));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // subtract 0x78 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    mybeforeoffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case  - could not get current compile buffer's length 2\n");
        return;
    }

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x78);

    myafteroffset = dg_getbufferlength(
        &BHarrayhead, 
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case  - could not get current compile buffer's length 3\n");
        return;
    }

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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case  - error compiling test routine\n");
        return;
    }
    
    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x78)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case - return not 0x20, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (4 != (myafteroffset - mybeforeoffset))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x78 success case - compiled instruction not 4 bytes, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (myafteroffset - mybeforeoffset));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // 0x80 case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x80 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rax);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x80);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rax,
        dg_rsp);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_rcx);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x80 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x80 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x80)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x80 success case - return not 0x10, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // 0x1000 case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x1000 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rax);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x1000);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rax,
        dg_rsp);

    dg_compilenegatereg(
        &BHarrayhead,
        dg_rcx);

    dg_compileaddregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x1000 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x1000 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x1000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilesubnfromrsp 0x1000 success case - return not 0x10, got ");
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


void testdg_compileaddntorsp()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;
    UINT64 mybeforeoffset = 0;
    UINT64 myafteroffset = 0;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileaddntorsp\n");

    // add 0x20 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case  - could not get current compile buffer's length\n");
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

    mybeforeoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case  - could not get current compile buffer's length 2\n");
        return;
    }

    dg_compileaddntorsp(
        &BHarrayhead,
        0x20);

    myafteroffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case  - could not get current compile buffer's length 3\n");
        return;
    }

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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x08)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case - return not 0x08, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (4 != (myafteroffset - mybeforeoffset))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x20 success case - compiled instruction not 4 bytes, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (myafteroffset - mybeforeoffset));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // add 0x78 success case
    //   assumes dg_compilesubnfromrsp works
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x78);

    mybeforeoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case  - could not get current compile buffer's length 2\n");
        return;
    }

    dg_compileaddntorsp(
        &BHarrayhead,
        0x78);

    myafteroffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case  - could not get current compile buffer's length 3\n");
        return;
    }

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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case - return not 0x00, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (4 != (myafteroffset - mybeforeoffset))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x78 success case - compiled instruction not 4 bytes, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (myafteroffset - mybeforeoffset));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // add 0x80 success case
    //   assumes dg_compilesubnfromrsp works
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x80 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x80 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x80);

    dg_compileaddntorsp(
        &BHarrayhead,
        0x80);

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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x80 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x80 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x80 success case - return not 0x00, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // add 0x800 success case
    //   assumes dg_compilesubnfromrsp works
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x800 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x800 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rsp,
        dg_rcx);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x800);

    dg_compileaddntorsp(
        &BHarrayhead,
        0x800);

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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x800 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x800 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddntorsp 0x800 success case - return not 0x00, got ");
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
	
	// mac os x requires memory to be used in units of system pagesize
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
	
	// mac os x requires memory to be used in units of system pagesize
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
	
	// if calling dg_growbuffer does not change the buffer's base address, you might be able to manually use a new buffer, and copy the data from one to the other
	
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


// this test is not platform independent...
void testdg_determineparameterregistermac()
{
    Bufferhandle BHarrayhead;
    
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 paramregister;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_determineparameterregister\n");
    
    
    // 0 int parameters extra floats success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcparameters, // offset
		0);                     // data);
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters, // offset
		0);                     // data); 
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_extraparametersfloatsflag, // offset
		FORTH_TRUE);                     // data);        
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        0);              // parameterindex);
        
    if (paramregister != dg_xmm0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra floats param 0 success case - expected dg_xmm0 (0x50), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        1);              // parameterindex);
        
    if (paramregister != dg_xmm1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra floats param 1 success case - expected dg_xmm1 (0x51), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        7);              // parameterindex);
        
    if (paramregister != dg_xmm7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra floats param 7 success case - expected dg_xmm7 (0x57), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        8);              // parameterindex);
        
    if (paramregister != dg_cparameteronstackflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra floats param 8 success case - expected dg_cparameteronstackflag (0x0100000000000000), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        9);              // parameterindex);
        
    if (paramregister != dg_cparameteronstackflag + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra floats param 9 success case - expected dg_cparameteronstackflag + 1 (0x0100000000000001), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // 0 int parameters extra ints success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcparameters, // offset
		0);                     // data);
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters, // offset
		0);                     // data); 
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_extraparametersfloatsflag, // offset
		FORTH_FALSE);                     // data);        
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        0);              // parameterindex);
        
    if (paramregister != dg_rdi)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 0 success case - expected dg_rdi, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        1);              // parameterindex);
        
    if (paramregister != dg_rsi)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 1 success case - expected dg_rsi, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        5);              // parameterindex);
        
    if (paramregister != dg_r9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 5 success case - expected dg_r9, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        6);              // parameterindex);
        
    if (paramregister != dg_cparameteronstackflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 6 success case - expected dg_cparameteronstackflag (0x0100000000000000), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        7);              // parameterindex);
        
    if (paramregister != dg_cparameteronstackflag + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 7 success case - expected dg_cparameteronstackflag + 1 (0x0100000000000001), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // 1 int parameter success case
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcparameters, // offset
		1);                     // data);
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters, // offset
		0);                     // data);
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_extraparametersfloatsflag, // offset
		FORTH_TRUE);                     // data);         
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        0);              // parameterindex);
        
    if (paramregister != dg_rdi)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 0 success case - expected dg_rdi (0x3f), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        1);              // parameterindex);
        
    if (paramregister != dg_xmm0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 1 success case - expected dg_xmm0 (0x50), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        8);              // parameterindex);
        
    if (paramregister != dg_xmm7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 8 success case - expected dg_xmm7 (0x57), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        9);              // parameterindex);
        
    if (paramregister != 0x0100000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 9 success case - expected dg_cparameteronstackflag (0x0100000000000000), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        10);              // parameterindex);
        
    if (paramregister != 0x0100000000000001)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 10 success case - expected dg_cparameteronstackflag + 1 (0x0100000000000001), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // 7 int parameters success case
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcparameters, // offset
		7);                     // data);
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters, // offset
		0);                     // data);
  
    dg_putbufferuint64 (
        &BHarrayhead,
		DG_DATASPACE_BUFFERID,
        dg_extraparametersfloatsflag, // offset
		FORTH_TRUE);                     // data);    
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        0);              // parameterindex);
        
    if (paramregister != dg_rdi)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 0 success case - expected dg_rdi (0x3f), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        1);              // parameterindex);
        
    if (paramregister != dg_rsi)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 1 success case - expected dg_rsi (0x3e), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        2);              // parameterindex);
        
    if (paramregister != dg_rdx)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 2 success case - expected dg_rdx (0x3a), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        3);              // parameterindex);
        
    if (paramregister != dg_rcx)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 3 success case - expected dg_rcx (0x3b), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        4);              // parameterindex);
        
    if (paramregister != dg_r8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 4 success case - expected dg_r8 (0x30), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        5);              // parameterindex);
        
    if (paramregister != dg_r9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 5 success case - expected dg_r9 (0x31), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        6);              // parameterindex);
        
    if (paramregister != 0x0100000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 6 success case - expected dg_cparameteronstackflag (0x0100000000000000), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        7);              // parameterindex);
        
    if (paramregister != dg_xmm0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 7 success case - expected dg_xmm0 (0x50), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        8);              // parameterindex);
        
    if (paramregister != dg_xmm1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 8 success case - expected dg_xmm1 (0x51), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        14);              // parameterindex);
        
    if (paramregister != dg_xmm7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 14 success case - expected dg_xmm7 (0x57), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    paramregister =  dg_determineparameterregister (
        &BHarrayhead,
        15);              // parameterindex);
        
    if (paramregister != 0x0100000000000001)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 15 success case - expected dg_cparameteronstackflag + 1 (0x0100000000000001), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}

// this test is not platform independent...
void testdg_determineparameterregisterwin()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 paramregister;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_determineparameterregister\n");


    // 0 int parameters extra ints success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters, // offset
        0);                     // data);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 8, // offset
        0);                     // data); 

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 0x10, // offset
        0);                     // data); 

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 0x18, // offset
        0);                     // data);      

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        0);              // parameterindex);

    if (paramregister != dg_rcx)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 0 success case - expected dg_rcx (0x039), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        1);              // parameterindex);

    if (paramregister != dg_rdx)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 1 success case - expected dg_cparameterpassinbothflag + 1 (0x0300000000000001), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        7);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 7 success case - expected dg_cparameteronstackflag + 3 (0x0100000000000003), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        8);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 8 success case - expected dg_cparameteronstackflag + 4 (0x0100000000000004), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        9);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 0 int params extra ints param 9 success case - expected dg_cparameteronstackflag + 5 (0x0100000000000005), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // 1 int parameter success case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters, // offset
        0);                     // data);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 8, // offset
        1);                     // data); 

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 0x10, // offset
        1);                     // data); 

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 0x18, // offset
        1);                     // data);            

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        0);              // parameterindex);

    if (paramregister != dg_rcx)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 0 success case - expected dg_rcx (0x39), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        1);              // parameterindex);

    if (paramregister != dg_xmm1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 1 success case - expected dg_xmm1 (0x51), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        8);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 8 success case - expected dg_cparameteronstackflag+4 (0x0100000000000004), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        9);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 9 success case - expected dg_cparameteronstackflag + 5 (0x0100000000000005), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        10);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 1 int params extra float param 10 success case - expected dg_cparameteronstackflag + 6 (0x0100000000000006), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // 7 int parameters success case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters, // offset
        0);                     // data);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 8, // offset
        0);                     // data); 

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 0x10, // offset
        0);                     // data); 

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_cparameterregisters + 0x18, // offset
        0);                     // data);    

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        0);              // parameterindex);

    if (paramregister != dg_rcx)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 0 success case - expected dg_rcx (0x39), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        1);              // parameterindex);

    if (paramregister != dg_rdx)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 1 success case - expected dg_rdx (0x3a), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        2);              // parameterindex);

    if (paramregister != dg_r8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 2 success case - expected dg_r8 (0x30), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        3);              // parameterindex);

    if (paramregister != dg_r9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 3 success case - expected dg_r9 (0x31), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        4);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 4 success case - expected dg_cparameteronstackflag (0x0100000000000000), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        5);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 5 success case - dg_cparameteronstackflag + 1 (0x0100000000000001), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        6);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 6 success case - expected dg_cparameteronstackflag + 2 (0x0100000000000002), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        7);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 7 success case - expected dg_cparameteronstackflag + 3 (0x0100000000000003), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        8);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 8 success case - expected dg_cparameteronstackflag + 4 (0x0100000000000004), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        14);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 10)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 14 success case - expected dg_cparameteronstackflag + 10 (0x010000000000000A), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    paramregister = dg_determineparameterregister(
        &BHarrayhead,
        15);              // parameterindex);

    if (paramregister != dg_cparameteronstackflag + 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_determineparameterregister 7 int params extra float param 15 success case - expected dg_cparameteronstackflag + 11 (0x010000000000000B), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, paramregister);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_determineparameterregister()
{
#ifdef DGLU_OS_WIN64
    testdg_determineparameterregisterwin();
#endif

#ifdef DGLU_OS_FREEBSD
    testdg_determineparameterregistermac();
#endif
}


void testdg_compileaddnlocalstocallsubsframe()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileaddnlocalstocallsubsframe\n");

    // add 0x00 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe 0x00 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe 0x00 success case  - could not get current compile buffer's length\n");
        return;
    }
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rax);
    
    dg_forthentercallsubsframecomma(&BHarrayhead);
    
    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0);
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rcx);
        
    dg_compilenegatereg (
        &BHarrayhead,
        dg_rcx);
        
    dg_compileaddregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe 0x00 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe 0x00 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe subtract 0x00 success case - return not 0x28, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // add 1 local (-0x08) success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -1 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -1 success case  - could not get current compile buffer's length\n");
        return;
    }
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rax);
    
    dg_forthentercallsubsframecomma(&BHarrayhead);
    
    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        1);
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rcx);
        
    dg_compilenegatereg (
        &BHarrayhead,
        dg_rcx);
        
    dg_compileaddregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -1 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -1 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x30)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -1 success case - return not 0x28, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // add 10 local (-0x50) success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -10 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -10 success case  - could not get current compile buffer's length\n");
        return;
    }
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rax);
    
    dg_forthentercallsubsframecomma(&BHarrayhead);
    
    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0X0A);
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rcx);
        
    dg_compilenegatereg (
        &BHarrayhead,
        dg_rcx);
        
    dg_compileaddregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -10 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -10 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x78)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -10 success case - return not 0x78, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // add 11 local (-0x58) success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -11 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -11 success case  - could not get current compile buffer's length\n");
        return;
    }
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rax);
    
    dg_forthentercallsubsframecomma(&BHarrayhead);
    
    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0X0B);
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rcx);
        
    dg_compilenegatereg (
        &BHarrayhead,
        dg_rcx);
        
    dg_compileaddregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -11 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -11 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x80)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -11 success case - return not 0x80, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // add 12 local (-0x88) success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -12 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -12 success case  - could not get current compile buffer's length\n");
        return;
    }
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rax);
    
    dg_forthentercallsubsframecomma(&BHarrayhead);
    
    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0X0C);
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rcx);
        
    dg_compilenegatereg (
        &BHarrayhead,
        dg_rcx);
        
    dg_compileaddregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -12 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -12 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x88)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -12 success case - return not 0x80, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // add 16 local (-0xA8) success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -16 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -16 success case  - could not get current compile buffer's length\n");
        return;
    }
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rax);
    
    dg_forthentercallsubsframecomma(&BHarrayhead);
    
    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0X10);
    
    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rsp,
        dg_rcx);
        
    dg_compilenegatereg (
        &BHarrayhead,
        dg_rcx);
        
    dg_compileaddregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -16 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -16 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0xA8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileaddnlocalstocallsubsframe -16 success case - return not 0xA8, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}




void testdg_compileobtoptodatastack()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();
    unsigned char* paddr;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileobtoptodatastack\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileobtoptodatastack success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileobtoptodatastack success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        (UINT64)&BHarrayhead,
        dg_param1reg);
    
    dg_compileinitlocals(&BHarrayhead);

    dg_compilemovntoreg(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_param2reg);

    dg_compilemovntoreg(
        &BHarrayhead,
        currentcompilebuffer,
        dg_param3reg);

    dg_compileobtoptodatastack(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID, // mycurrentcompilebuffer,
        currentcompilebuffer); // mystartoffset);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x1122554477,
        dg_rax);

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileobtoptodatastack success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileobtoptodatastack success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x1122554477)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileobtoptodatastack success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x1122554477);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_popdatastack(&BHarrayhead);

    paddr = dg_getpbufferoffset(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (x != (UINT64)paddr)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileobtoptodatastack success case - data stack not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)paddr);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_compilemovbracketrbpd8toreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrbpd8toreg\n");

    // success [RBP-8] -> RAX case 
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RAX case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RAX case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RAX case  - error compiling enter frame\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrbpd8toreg (
    	&BHarrayhead,
        (UINT64)dg_rax, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RAX case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        8);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RAX case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RAX case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RAX case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success [RBP-8] -> RCX case 
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RCX case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RCX case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RCX case  - error compiling enter frame\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        (UINT64)dg_rcx); // reg)

    dg_compilemovbracketrbpd8toreg (
    	&BHarrayhead,
        (UINT64)dg_rcx, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RCX case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        8);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RCX case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RCX case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> RCX case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success [RBP-8] -> R8 case 
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R8 case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R8 case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R8 case  - error compiling enter frame\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        (UINT64)dg_r8); // reg)

    dg_compilemovbracketrbpd8toreg (
    	&BHarrayhead,
        (UINT64)dg_r8, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R8 case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        8);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R8 case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R8 case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R8 case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success [RBP-8] -> R9 case 
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R9 case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R9 case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R9 case  - error compiling enter frame\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        (UINT64)dg_r9); // reg)

    dg_compilemovbracketrbpd8toreg (
    	&BHarrayhead,
        (UINT64)dg_r9, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R9 case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        8);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r9,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R9 case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R9 case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8toreg success [RBP-8] -> R9 case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovbracketrbpd8tofreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    FLOAT64 x;

    FLOAT64(*pfunct)(FLOAT64 y); // to initialize xmm0

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrbpd8tofreg\n");

    // success xmm0 case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - error compiling enter frame\n");
        return;
    }
      
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovbracketrbpd8tofreg (
    	&BHarrayhead,
        (UINT64)dg_xmm0, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - error doing dg_compilemovbracketrbpdtofreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)(FLOAT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0.0);

    if (*((UINT64*)&x) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)&x));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // success xmm1 case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm1 case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm1 case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm1 case  - error compiling enter frame\n");
        return;
    }
      
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovbracketrbpd8tofreg (
    	&BHarrayhead,
        (UINT64)dg_xmm1, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm1 case  - error doing dg_compilemovbracketrbpdtofreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)(FLOAT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0.0);

    if (*((UINT64*)&x) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg success xmm0 case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)&x));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // success case xmm8
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm8 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm8 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm8 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm1); // preserving reg
      
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovbracketrbpd8tofreg (
    	&BHarrayhead,
        (UINT64)dg_xmm8, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm0);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm8); // unpreserving reg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm8 success case  - error doing dg_compilemovbracketrbpdtofreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)(FLOAT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0.0);

    if (*((UINT64*)&x) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm8 success case - return not correct, expected not ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)&x));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success case xmm9
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm9 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm9 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm9 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm1); // preserving freg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm9,
        dg_xmm2); // preserving freg
      
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovbracketrsptofreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compilemovbracketrbpd8tofreg (
    	&BHarrayhead,
        (UINT64)dg_xmm9, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm9,
        dg_xmm0);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm8); // unpreserving freg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm2,
        dg_xmm9); // unpreserving freg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm9 success case  - error doing dg_compilemovbracketrbpdtofreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm9 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (FLOAT64(*)(FLOAT64))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm9 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(0.0);

    if (*((UINT64*)&x) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd8tofreg xmm9 success case - return not correct, expected not ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)&x));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }



    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovbracketrsptoreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrsptoreg\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - could not get current compile buffer's length\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrsptoreg (
    	&BHarrayhead,
        (UINT64)dg_rax); // reg) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - could not get current compile buffer's length\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrsptoreg (
    	&BHarrayhead,
        (UINT64)dg_rcx); // reg) 

    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // r8 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r8 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r8 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rdx);
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrsptoreg (
    	&BHarrayhead,
        (UINT64)dg_r8); // reg) 

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rdx,
        dg_r8);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r8 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // r9 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r9 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r9 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r9,
        dg_rdx);
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrsptoreg (
    	&BHarrayhead,
        (UINT64)dg_r9); // reg) 

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r9,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rdx,
        dg_r9);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r9 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r9 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r9 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrsptoreg r9 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}



void testdg_compilemovbracketrspd8toreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrspd8toreg\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg success case  - could not get current compile buffer's length\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x5, // n,
        (UINT64)dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrspd8toreg (
    	&BHarrayhead,
        (UINT64)dg_rax, // reg,
        0x08); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg rcx success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg rcx success case  - could not get current compile buffer's length\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x5, // n,
        (UINT64)dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrspd8toreg (
    	&BHarrayhead,
        (UINT64)dg_rcx, // reg,
        0x08); // displacement)

    dg_compilemovregtoreg (
        &BHarrayhead,
        (UINT64)dg_rcx,
        (UINT64)dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg rcx success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg rcx success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg rcx success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg rcx success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // r8 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r8 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r8 success case  - could not get current compile buffer's length\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x5, // n,
        (UINT64)dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrspd8toreg (
    	&BHarrayhead,
        (UINT64)dg_r8, // reg,
        0x08); // displacement)

    dg_compilemovregtoreg (
        &BHarrayhead,
        (UINT64)dg_r8,
        (UINT64)dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r8 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // r9 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r9 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r9 success case  - could not get current compile buffer's length\n");
        return;
    }
        
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x5, // n,
        (UINT64)dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        (UINT64)dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovbracketrspd8toreg (
    	&BHarrayhead,
        (UINT64)dg_r9, // reg,
        0x08); // displacement)

    dg_compilemovregtoreg (
        &BHarrayhead,
        (UINT64)dg_r9,
        (UINT64)dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r9 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r9 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r9 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd8toreg r9 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovbracketrbpd32toreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrbpd32toreg\n");

    // success [rbp-0x98]->rax case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpd32toreg (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success [rbp-0x98]->rcx case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rcx success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rcx success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rcx success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpd32toreg (
    	&BHarrayhead,
        dg_rcx, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rcx success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rcx success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rcx success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->rax success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success [rbp-0x98]->r8 case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r8 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r8 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r8 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpd32toreg (
    	&BHarrayhead,
        dg_r8, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r8 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success [rbp-0x98]->r9 case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r9 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r9 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r9 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpd32toreg (
    	&BHarrayhead,
        dg_r9, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r9,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r9 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r9 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r9 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg [rbp-0x98]->r9 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovbracketrbpd32tofreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrbpd32tofreg\n");

    // success xmm0 case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg success xmm0 case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg success xmm0 case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg success xmm0 case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x18);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptoreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpd32tofreg (
    	&BHarrayhead,
        dg_xmm0, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm0 case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilemovfregtobracketrsp(
        &BHarrayhead,
        dg_xmm0);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm0 case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm0 case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm0 case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // success xmm1 case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg success xmm1 case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg success xmm1 case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg success xmm1 case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x18);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptoreg(
        &BHarrayhead,
        dg_xmm1);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd32tofreg (
    	&BHarrayhead,
        dg_xmm1, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    dg_compilemovfregtobracketrsp(
        &BHarrayhead,
        dg_xmm1);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm1 case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm1 case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm1 case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg success xmm1 case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // [RBP+80]->XMM8 case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg xmm8 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg xmm8 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm1); // preserving must be preserved freg

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x18);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptoreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovbracketrsptoreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd32tofreg (
    	&BHarrayhead,
        dg_xmm8, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilemovfregtobracketrsp(
        &BHarrayhead,
        dg_xmm8);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm8); // unpreserving must be preserved freg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP+80]->XMM9 case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg xmm9 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32tofreg xmm9 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm1); // preserving must be preserved freg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm9,
        dg_xmm2); // preserving must be preserved freg

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x18);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrsptoreg(
        &BHarrayhead,
        dg_xmm0);

    dg_compilemovbracketrsptoreg(
        &BHarrayhead,
        dg_xmm8);

    dg_compilemovbracketrsptoreg(
        &BHarrayhead,
        dg_xmm9);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd32tofreg (
    	&BHarrayhead,
        dg_xmm9, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilemovfregtobracketrsp(
        &BHarrayhead,
        dg_xmm9);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm8); // unpreserving must be preserved freg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm2,
        dg_xmm9); // unpreserving must be preserved freg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpd32toreg xmm8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}



void testdg_compilemovbracketrspd32toreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrspd32toreg\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrspd32toreg (
    	&BHarrayhead,
        dg_rax, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg rcx success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg rcx success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrspd32toreg (
    	&BHarrayhead,
        dg_rcx, // reg,
        0x90); // displacement)

    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg rcx success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg rcx success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r8 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r8 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrspd32toreg (
    	&BHarrayhead,
        dg_r8, // reg,
        0x90); // displacement)

    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_r8,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r8 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r9 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r9 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r9 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_r8); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_r9); // reg)

    dg_compilemovbracketrspd32toreg (
    	&BHarrayhead,
        dg_r9, // reg,
        0x90); // displacement)

    dg_compilemovregtoreg (
        &BHarrayhead,
        dg_r9,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r9 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r9 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r9 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspd32toreg r9 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovbracketrbpdtoreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;
    FLOAT64 xf;

    UINT64(*pfunct)();
    FLOAT64(*pffunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrbpdtoreg\n");

    // success case [RBP-0x98]->RAX
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case  - could not get current compile buffer\n");
        return;
    }

    // [RBP-0x98]->RAX success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // [RBP-0x28]->RAX
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x80]->RAX
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case c - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x78);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case c - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x60);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x28]->RCX
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_rcx, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x28]->R8
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error compiling enter frame\n");
        return;
    }

    // +0 saved rbp

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    // +0 saved rbp
    // -x08 ?
    // -x10 ?
    // -x18 ?
    // -x20 ?
    
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    // +0 saved rbp
    // -x08 ?
    // -x10 ?
    // -x18 ?
    // -x20 ?
    // -x28 0x178326

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    // checking that rex form works ok...
    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_r8, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x28]->R9
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d2 - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d2 - error compiling enter frame\n");
        return;
    }

    // +0 saved rbp

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    // +0 saved rbp
    // -x08 ?
    // -x10 ?
    // -x18 ?
    // -x20 ?
    
    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    // +0 saved rbp
    // -x08 ?
    // -x10 ?
    // -x18 ?
    // -x20 ?
    // -x28 0x178326

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    // checking that rex form works ok...
    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_r9, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d2 - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r9,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d2 - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d2 - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case d2 - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x98]->XMM0 success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x98]->XMM0 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x98]->XMM0 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_xmm0, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x98]->XMM0 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x98]->XMM0 success case  - error compiling test routine\n");
        return;
    }

    pffunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x98]->XMM0 success case  - error getting start address of test function\n");
        return;
    }

    xf = pfunct();

    if (*((FLOAT64*)(&xf)) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x98]->XMM0 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead,  *((FLOAT64*)(&xf)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x28]->XMM0 success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM0 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM0 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_xmm0, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM0 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM0 success case  - error compiling test routine\n");
        return;
    }

    pffunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM0 success case  - error getting start address of test function\n");
        return;
    }

    xf = pfunct();

    if (*((FLOAT64*)(&xf)) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM0 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead,  *((FLOAT64*)(&xf)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x28]->XMM2 success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM2 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM2 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_xmm2, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    dg_compilemovfregtofreg (
    	&BHarrayhead,
        dg_xmm2, 
        dg_xmm0); 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM2 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM2 success case  - error compiling test routine\n");
        return;
    }

    pffunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM2 success case  - error getting start address of test function\n");
        return;
    }

    xf = pfunct();

    if (*((FLOAT64*)(&xf)) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM2 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead,  *((FLOAT64*)(&xf)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x28]->XMM8 success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM8 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM8 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm1); // preserving must be preserved freg

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_xmm8, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    dg_compilemovfregtofreg (
    	&BHarrayhead,
        dg_xmm8, 
        dg_xmm0); 

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm8); // unpreserving must be preserved freg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM8 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM8 success case  - error compiling test routine\n");
        return;
    }

    pffunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM8 success case  - error getting start address of test function\n");
        return;
    }

    xf = pfunct();

    if (*((FLOAT64*)(&xf)) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead,  *((FLOAT64*)(&xf)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [RBP-0x28]->XMM9 success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM9 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM9 success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm1); // preserving must be preserved freg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm9,
        dg_xmm2); // preserving must be preserved freg

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrbpdtoreg (
    	&BHarrayhead,
        dg_xmm9, // reg,
        -0x28); // displacement) (32 bit so should be ok with -value)

    dg_compilemovfregtofreg (
    	&BHarrayhead,
        dg_xmm9, 
        dg_xmm0); 

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm1,
        dg_xmm8); // unpreserving must be preserved freg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm2,
        dg_xmm9); // unpreserving must be preserved freg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM9 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM9 success case  - error compiling test routine\n");
        return;
    }

    pffunct = (FLOAT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM9 success case  - error getting start address of test function\n");
        return;
    }

    xf = pfunct();

    if (*((FLOAT64*)(&xf)) != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg [RBP-0x28]->XMM9 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead,  *((FLOAT64*)(&xf)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // could test out of range + or -....

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovbracketrspdtoreg()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovbracketrspdtoreg\n");

    // [rsp+0x90]->rax success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x90]->rax success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x90]->rax success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrspdtoreg (
    	&BHarrayhead,
        dg_rax, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x90]->rax success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x90]->rax success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x90]->rax success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x90]->rax success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [rsp+0x20]->rax success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x20]->rax success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x20);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrspdtoreg (
    	&BHarrayhead,
        dg_rax, // reg,
        0x20); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x20]->rax success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x20]->rax success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x20]->rax success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x20]->rax success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [rsp+0x80]->rax success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x80]->rax success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x78);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
    	0x08);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrspdtoreg (
    	&BHarrayhead,
        dg_rax, // reg,
        0x80); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x80]->rax success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x28);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x60);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x80]->rax success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x80]->rax success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rax success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [rsp+0x00]->rax success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rax success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovbracketrspdtoreg (
    	&BHarrayhead,
        dg_rax, // reg,
        0x00); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rax success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x08);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rax success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rax success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rax success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [rsp+0x00]->rcx success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rcx success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rcx); // reg)

    dg_compilemovbracketrspdtoreg (
    	&BHarrayhead,
        dg_rcx, // reg,
        0x00); // displacement) 

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_rcx,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rcx success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x08);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rcx success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rcx success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->rcx success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [rsp+0x00]->r8 success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r8 success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_r8); // reg)

    dg_compilemovbracketrspdtoreg (
    	&BHarrayhead,
        dg_r8, // reg,
        0x00); // displacement) 

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r8,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r8 success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x08);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r8 success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r8 success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // [rsp+0x00]->r9 success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r9 success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( // "\x50" 2 bytes
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_r8); // reg)

    dg_compilemovbracketrspdtoreg (
    	&BHarrayhead,
        dg_r9, // reg,
        0x00); // displacement) 

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_r9,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r9 success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x08);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r9 success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r9 success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrspdtoreg [rsp+0x00]->r9 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // could test out of range + or -....

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovregtobracketrbpd8()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtobracketrbpd8\n");

    // RAX->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RAX->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RAX->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RAX->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrbpd8 (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RAX->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RAX->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RAX->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RAX->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // RCX->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RCX->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RCX->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RCX->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrbpd8 (
    	&BHarrayhead,
        dg_rcx, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RCX->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RCX->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RCX->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 RCX->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // R8->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R8->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R8->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R8->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrbpd8 (
    	&BHarrayhead,
        dg_r8, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R8->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R8->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R8->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R8->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // R9->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R9->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R9->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R9->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_r8); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovregtobracketrbpd8 (
    	&BHarrayhead,
        dg_r9, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R9->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R9->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R9->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd8 R9->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovfregtobracketrbpd8()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovfregtobracketrbpd8\n");

    // XMM0 ->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM0->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM0->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM0->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovfregtobracketrbpd8 (
    	&BHarrayhead,
        dg_xmm0, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM0->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM0->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM0->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilefmovregtobracketrbpd8 XMM0->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // XMM2 ->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM2->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM2->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM2->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm2,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x08);

    dg_compilemovfregtobracketrbpd8 (
    	&BHarrayhead,
        dg_xmm2, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM2->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM2->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM2->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM2->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // XMM8 ->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM8->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM8->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM8->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm8,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x08);

    dg_compilemovfregtobracketrbpd8 (
    	&BHarrayhead,
        dg_xmm8, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM8->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM8->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM8->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM8->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // XMM10 ->[RBP-0x08] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM10->[RBP-0x08] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM10->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM10->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm2); // preserving must be preserved reg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm10,
        dg_xmm3); // preserving must be preserved reg

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm10,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x08);

    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm8,
        -0x08);

    dg_compilemovfregtobracketrbpd8 (
    	&BHarrayhead,
        dg_xmm10, // reg,
        -0x08); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM10->[RBP-0x08] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm2,
        dg_xmm8); // unpreserving must be preserved reg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm3,
        dg_xmm10); // unpreserving must be preserved reg

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM10->[RBP-0x08] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM10->[RBP-0x08] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd8 XMM10->[RBP-0x08] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovfregtobracketrbpd32()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;
    // UINT64 mytestoffset;
    // unsigned char* pbuf;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovfregtobracketrbpd32\n");

    // XMM0 ->[RBP-0x88] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM0->[RBP-0x88] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM0->[RBP-0x08] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM0->[RBP-0x08] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x80);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovfregtobracketrbpd32 (
    	&BHarrayhead,
        dg_xmm0, // reg,
        -0x88); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM0->[RBP-0x88] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM0->[RBP-0x88] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM0->[RBP-0x88] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilefmovregtobracketrbpd32 XMM0->[RBP-0x88] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // XMM2 ->[RBP-0x88] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM2->[RBP-0x88] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM2->[RBP-0x88] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM2->[RBP-0x88] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm2,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilesubnfromrsp(
       &BHarrayhead,
       0x80);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd32tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x88);

    dg_compilemovfregtobracketrbpd32 (
    	&BHarrayhead,
        dg_xmm2, // reg,
        -0x88); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM2->[RBP-0x88] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM2->[RBP-0x88] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM2->[RBP-0x88] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM2->[RBP-0x88] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // XMM8 ->[RBP-0x88] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM8->[RBP-0x88] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM8->[RBP-0x88] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM8->[RBP-0x88] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm2);  // preserving must be preserved reg

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm8,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x80);

    dg_compilemovntoreg(
        &BHarrayhead,
        1, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd32tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x88);

    // mytestoffset = dg_getbufferlength(
    //    &BHarrayhead,
    //    mycurrentcompilebuffer);

    dg_compilemovfregtobracketrbpd32 (
    	&BHarrayhead,
        dg_xmm8, // reg,
        -0x88); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    // pbuf = dg_getpbufferoffset(
    //    &BHarrayhead,
    //    mycurrentcompilebuffer,
    //    mytestoffset);

    // dg_hexdumpsegment (
    //    &BHarrayhead,
    //    pbuf,
    //    0x10);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm2,
        dg_xmm8);  // unpreserving must be preserved reg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM8->[RBP-0x88] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM8->[RBP-0x88] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM8->[RBP-0x88] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM8->[RBP-0x88] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // XMM10 ->[RBP-0x88] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM10->[RBP-0x88] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM10->[RBP-0x88] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM10->[RBP-0x88] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm8,
        dg_xmm2);  // preserving must be preserved reg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm10,
        dg_xmm3);  // preserving must be preserved reg

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    // tested already
    dg_compilemovbracketrbpd8tofreg(
        &BHarrayhead,
        dg_xmm10,
        -0x08);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilesubnfromrsp(
        &BHarrayhead,
        0x80);

    dg_compilemovntoreg(
        &BHarrayhead,
        1, // n,
        dg_rax); // reg)

    dg_compilepushregtoret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovbracketrbpd32tofreg(
        &BHarrayhead,
        dg_xmm0,
        -0x88);

    dg_compilemovbracketrbpd32tofreg(
        &BHarrayhead,
        dg_xmm8,
        -0x88);

    // mytestoffset = dg_getbufferlength(
    //    &BHarrayhead,
    //    mycurrentcompilebuffer);

    dg_compilemovfregtobracketrbpd32 (
    	&BHarrayhead,
        dg_xmm10, // reg,
        -0x88); // displacement) (32 bit so should be ok with -value)

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    // pbuf = dg_getpbufferoffset(
    //    &BHarrayhead,
    //    mycurrentcompilebuffer,
    //    mytestoffset);

    // dg_hexdumpsegment (
    //    &BHarrayhead,
    //    pbuf,
    //    0x10);

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm2,
        dg_xmm8);  // unpreserving must be preserved reg

    dg_compilemovfregtofreg(
        &BHarrayhead,
        dg_xmm3,
        dg_xmm10);  // unpreserving must be preserved reg

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM10->[RBP-0x88] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM10->[RBP-0x88] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM10->[RBP-0x88] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovfregtobracketrbpd32 XMM10->[RBP-0x88] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}



void testdg_compilemovregtobracketrsp()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtobracketrsp\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rax success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rax success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrsp (
    	&BHarrayhead,
        dg_rax); // reg) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rax success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rax success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rax success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rax success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rcx success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rcx success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrsp (
    	&BHarrayhead,
        dg_rcx); // reg) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rcx success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rcx success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rcx success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp rcx success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r8 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r8 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrsp (
    	&BHarrayhead,
        dg_r8); // reg) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r8 success case  - error doing dg_compilemovregtobracketrsp\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r8 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r8 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"*******************************\n ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r8 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            0x20);
        return;
    }


    // r9 success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r9 success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r9 success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_r8); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovregtobracketrsp (
    	&BHarrayhead,
        dg_r9); // reg) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r9 success case  - error doing dg_compilemovregtobracketrsp\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r9 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r9 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"*******************************\n ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrsp r9 success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            0x20);
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovregtobracketrspd8()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtobracketrspd8\n");

    // rax->[rsp+8] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rax->[rsp+8] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rax->[rsp+8] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
    	&BHarrayhead,
        dg_rax, // reg,
        0x08); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rax->[rsp+8] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rax->[rsp+8] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rax->[rsp+8] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rax->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx->[rsp+8] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rcx->[rsp+8] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rcx->[rsp+8] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrspd8 (
    	&BHarrayhead,
        dg_rcx, // reg,
        0x08); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rcx->[rsp+8] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rcx->[rsp+8] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rcx->[rsp+8] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 rcx->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8->[rsp+8] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r8->[rsp+8] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r8->[rsp+8] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrspd8 (
    	&BHarrayhead,
        dg_r8, // reg,
        0x08); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r8->[rsp+8] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r8->[rsp+8] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r8->[rsp+8] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r8->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r10->[rsp+8] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r10->[rsp+8] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r10->[rsp+8] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r10); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrspd8 (
    	&BHarrayhead,
        dg_r10, // reg,
        0x08); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r10->[rsp+8] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r10->[rsp+8] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r10->[rsp+8] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd8 r10->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovregtobracketrbpd32()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtobracketrbpd32\n");

    // rax->[rbp-0x98] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rax->[rbp-0x98] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rax->[rbp-0x98] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rax->[rbp-0x98] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrbpd32 (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rax->[rbp-0x98] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rax->[rbp-0x98] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rax->[rbp-0x98] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rax->[rbp-0x98] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // rcx->[rbp-0x98] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rcx->[rbp-0x98] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rcx->[rbp-0x98] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rcx->[rbp-0x98] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrbpd32 (
    	&BHarrayhead,
        dg_rcx, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rcx->[rbp-0x98] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rcx->[rbp-0x98] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rcx->[rbp-0x98] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 rcx->[rbp-0x98] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8->[rbp-0x98] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r8->[rbp-0x98] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r8->[rbp-0x98] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r8->[rbp-0x98] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrbpd32 (
    	&BHarrayhead,
        dg_r8, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r8->[rbp-0x98] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r8->[rbp-0x98] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r8->[rbp-0x98] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r8->[rbp-0x98] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r9->[rbp-0x80] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r9->[rbp-0x80] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r9->[rbp-0x80] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r9->[rbp-0x80] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x10);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrbpd32 (
    	&BHarrayhead,
        dg_r9, // reg,
        -0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r9->[rbp-0x80] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x08);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r9->[rbp-0x80] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r9->[rbp-0x80] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd32 r9->[rbp-0x80] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovregtobracketrspd32()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtobracketrspd32\n");

    // rax->[rsp+0x90] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rax->[rsp+0x90] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rax->[rsp+0x90] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd32 (
    	&BHarrayhead,
        dg_rax, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rax->[rsp+0x90] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rax->[rsp+0x90] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rax->[rsp+0x90] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rax->[rsp+0x90] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success rcx->[rsp+0x90] case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rcx->[rsp+0x90] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rcx->[rsp+0x90] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrspd32 (
    	&BHarrayhead,
        dg_rcx, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rcx->[rsp+0x90] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rcx->[rsp+0x90] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rcx->[rsp+0x90] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 rcx->[rsp+0x90] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success r8->[rsp+0x90] case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r8->[rsp+0x90] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r8->[rsp+0x90] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrspd32 (
    	&BHarrayhead,
        dg_r8, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r8->[rsp+0x90] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r8->[rsp+0x90] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r8->[rsp+0x90] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r8->[rsp+0x90] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // success r9->[rsp+0x90] case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r9->[rsp+0x90] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r9->[rsp+0x90] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrspd32 (
    	&BHarrayhead,
        dg_r9, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r9->[rsp+0x90] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r9->[rsp+0x90] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r9->[rsp+0x90] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd32 r9->[rsp+0x90] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovregtobracketrbpd()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtobracketrbpd\n");

    // rax->[rbp-0x98] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x98] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x98] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x98] success case  - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x98); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x98] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x98] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x98] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x98] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // rax->[rbp-0x80] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x80] success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x80] success case b - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x80] success case b - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x78);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x80] success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x80] success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-0x80] success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8->[rbp-0x80] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-0x80] success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-0x80] success case b - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_r8, // reg,
        -0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-0x80] success case b - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x78);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-0x80] success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-0x80] success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-0x80] success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r9->[rbp-0x80] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-0x80] success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-0x80] success case b - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_r9, // reg,
        -0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-0x80] success case b - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x78);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-0x80] success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-0x80] success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-0x80] success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // rax->[rbp-8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-8] success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-8] success case c - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_rax, // reg,
        -0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-8] success case c - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-8] success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-8] success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rax->[rbp-8] success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // rcx->[rbp-8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rcx->[rbp-8] success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rcx->[rbp-8] success case c - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_rcx, // reg,
        -0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rcx->[rbp-8] success case c - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rcx->[rbp-8] success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rcx->[rbp-8] success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd rcx->[rbp-8] success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8->[rbp-8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-8] success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-8] success case c - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_r8, // reg,
        -0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-8] success case c - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-8] success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-8] success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r8->[rbp-8] success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r9->[rbp-8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-8] success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-8] success case c - error compiling enter frame\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrbpd (
    	&BHarrayhead,
        dg_r9, // reg,
        -0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-8] success case c - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-8] success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-8] success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrbpd r9->[rbp-8] success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilemovregtobracketrspd()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilemovregtobracketrspd\n");

    // rax->[rsp+0x90] success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x90] success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x90] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rax, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x90] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x90] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x90] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x90] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx->[rsp+0x90] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x90] success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x70);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x28);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rcx, // reg,
        0x90); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x90] success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x70);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x90] success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x90] success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x90] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rax->[rsp+0x80] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x80] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x48);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rax, // reg,
        0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x80] success casesuccess case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x78);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x08);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x80] success casesuccess case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x80] success case success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0x80] success case success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx->[rsp+0x80] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x80] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x48);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x40);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rcx, // reg,
        0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x80] success casesuccess case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x78);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x08);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x80] success casesuccess case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x80] success case success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0x80] success case success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rax->[rsp+8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+8] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x10);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rax, // reg,
        0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+8] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+8] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+8] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx->[rsp+8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+8] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x10);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rcx, // reg,
        0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+8] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+8] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+8] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8->[rsp+8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+8] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x10);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_r8, // reg,
        0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+8] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+8] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+8] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r9->[rsp+8] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+8] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x10);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_r8); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_r9, // reg,
        0x8); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+8] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+8] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+8] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+8] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // rax->[rsp+0] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rax, // reg,
        0); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rax->[rsp+0] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // rcx->[rsp+0] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rcx); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_rcx, // reg,
        0); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd rcx->[rsp+0] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r8->[rsp+0] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+0] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r8); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_r8, // reg,
        0); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+0] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+0] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+0] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r8->[rsp+0] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // r9->[rsp+0] success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+0] success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        0x8);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_r8); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_r9); // reg)

    dg_compilemovregtobracketrspd (
    	&BHarrayhead,
        dg_r9, // reg,
        0); // displacement) 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+0] success case - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+0] success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+0] success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovregtobracketrspd r9->[rsp+0] success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilepreservelocalsregstoret()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilepreservelocalsregstoret\n");

    // no regs preserved success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret no regs preserved success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret no regs preserved success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        0, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret no regs preserved success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret no regs preserved success case  - error compiling test routine\n");
        return;
    }

    x = mystartoffset;

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret no regs preserved success case  - could not get current compile buffer's length\n");
        return;
    }

    if (mystartoffset != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret no regs preserved success case  - code buffer length changed\n");
        return;
    }
 

    // localsregs[0] only success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[0] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[0]); // reg)

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        1, // localsregsmasktopreserve,
        1, // localsregsmaskallocated)
        0);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[0] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[0] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[0] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[1] only success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[1] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        2, // localsregsmasktopreserve,
        2, // localsregsmaskallocated)
        0);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[1] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[1] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[1] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[2] only success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[2]); // reg)

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        4, // localsregsmasktopreserve,
        4, // localsregsmaskallocated)
        0);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
 
    
    // localsregs[2] only success case b
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[2]); // reg)

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        4, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[2] only success case c
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[2]); // reg)

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        4, // localsregsmasktopreserve,
        0x0D, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[2] only success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[3] localsregs[1] success case a
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x3845621, // n,
        dg_localsregs[1]); // reg)

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        0x0A, // localsregsmasktopreserve,
        0x0A, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x21981387);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[3] localsregs[1] success case a
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x3845621, // n,
        dg_localsregs[1]); // reg)

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        0x0A, // localsregsmasktopreserve,
        0x0A, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        8);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x3845621)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[3] localsregs[1] success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[4] localsregs[3] localsregs[1] success case a
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2897356387, // n,
        dg_localsregs[4]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x3845621, // n,
        dg_localsregs[1]); // reg)

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        0x3F, // localsregsmasktopreserve,
        0x3F, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        8);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x2897356387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x2897356387);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[4] localsregs[3] localsregs[1] success case b
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2897356387, // n,
        dg_localsregs[4]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x3845621, // n,
        dg_localsregs[1]); // reg)

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        0x3F, // localsregsmasktopreserve,
        0x3F, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x2897356387);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[4] localsregs[3] localsregs[1] success case c
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2897356387, // n,
        dg_localsregs[4]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x3845621, // n,
        dg_localsregs[1]); // reg)

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        0x3F, // localsregsmasktopreserve,
        0x3F, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x3845621)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[4] localsregs[3] localsregs[1] success case d
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case d - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x2897356387, // n,
        dg_localsregs[4]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x3845621, // n,
        dg_localsregs[1]); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilesegment (
        &BHarrayhead, 
        (const char*)"\x90", 
        1);

    dg_compilepreservelocalsregstoret (
        &BHarrayhead,
        0x3F, // localsregsmasktopreserve,
        0x3F, // localsregsmaskallocated)
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case d - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x20);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[4]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case d - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case d - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x3845621)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[4] localsregs[3] localsregs[1] success case d - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilepreservenoframeregs()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilepreservenoframeregs\n");

    // no regs preserved success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - error initializing dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - error initializing dg_regspreserveddepth depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - error initializing dg_subroutineregspreserved depth\n");
        return;
    }


    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        largestunsignedint);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - error initializing dg_localsregsused depth\n");
        return;
    }

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepreservenoframeregs (
        &BHarrayhead,
        0); // regmask of locals regs to preserve

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - could not get current compile buffer's length\n");
        return;
    }

    if (mystartoffset != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - code buffer length changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (0 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - dg_returnstackdepth changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth);

    if (0 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - dg_regspreserveddepth changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved);

    if (0 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - dg_subroutineregspreserved changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (largestunsignedint != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs no regs preserved success case  - dg_localsregsused changed\n");
        return;
    }
 

    // localsregs[0] only success case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - error initializing dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - error initializing dg_regspreserveddepth depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - error initializing dg_subroutineregspreserved depth\n");
        return;
    }


    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        largestunsignedint);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - error initializing dg_localsregsused depth\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[0]); // reg)

    dg_compilepreservenoframeregs (
        &BHarrayhead,
        1); // regmask of locals regs to preserve

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[0] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservelocalsregstoret localsregs[0] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - dg_returnstackdepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth);

    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - dg_regspreserveddepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved);

    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - dg_subroutineregspreserved not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (0xfffffffffffffffe != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[0] only success case  - dg_localsregsused expected 0xfffffffffffffffe, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[1] only success case
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - error initializing dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - error initializing dg_regspreserveddepth depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - error initializing dg_subroutineregspreserved depth\n");
        return;
    }


    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        largestunsignedint);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - error initializing dg_localsregsused depth\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilepreservenoframeregs (
        &BHarrayhead,
        2); // regmask of locals regs to preserve

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - dg_returnstackdepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth);

    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - dg_regspreserveddepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved);

    if (2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - dg_subroutineregspreserved not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (0xfffffffffffffffd != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] only success case  - dg_localsregsused expected 0xfffffffffffffffe, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[1] and localsregs[3] success case a
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - error initializing dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - error initializing dg_regspreserveddepth depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - error initializing dg_subroutineregspreserved depth\n");
        return;
    }


    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        largestunsignedint);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - error initializing dg_localsregsused depth\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x98743532, // n,
        dg_localsregs[3]); // reg)

    dg_compilepreservenoframeregs (
        &BHarrayhead,
        0x0a); // regmask of locals regs to preserve

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax); // should be localsregs[1]

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax); // should be localsregs[3]

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x98743532)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x98743532);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_returnstackdepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth);

    if (2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_regspreserveddepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved);

    if (0x0a != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_subroutineregspreserved not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (0xfffffffffffffff5 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_localsregsused expected 0xfffffffffffffff5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[1] and localsregs[3] success case b
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b  - error initializing dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b  - error initializing dg_regspreserveddepth depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        38); // should get overwritten

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b  - error initializing dg_subroutineregspreserved depth\n");
        return;
    }


    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        0x7fffffffffffffff);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b  - error initializing dg_localsregsused depth\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x98743532, // n,
        dg_localsregs[3]); // reg)

    dg_compilepreservenoframeregs (
        &BHarrayhead,
        0x0a); // regmask of locals regs to preserve

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);  // should be localsregs[1]

    dg_compileaddn8torsp(
        &BHarrayhead,
        8);  // should be localsregs[3]

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x21981387);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (3 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_returnstackdepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth);

    if (3 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_regspreserveddepth not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved);

    if (0x0a != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_subroutineregspreserved not correct\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (0x7ffffffffffffff5 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservenoframeregs localsregs[1] and localsregs[3] success case a  - dg_localsregsused expected 0x7ffffffffffffff5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

/*
void testdg_compilepreservecallsubsregs()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilepreservecallsubsregs\n");

    // no regs preserved success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - error initializing dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - error initializing dg_regspreserveddepth depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - error initializing dg_subroutineregspreserved depth\n");
        return;
    }


    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused,
        largestunsignedint);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - error initializing dg_localsregsused depth\n");
        return;
    }

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        0); // regmask of locals regs to preserve

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    x = mystartoffset;

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - could not get current compile buffer's length\n");
        return;
    }

    if (mystartoffset != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - code buffer length changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (0 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - dg_returnstackdepth changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth);

    if (0 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - dg_regspreserveddepth changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved);

    if (0 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - dg_subroutineregspreserved changed\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localsregsused);

    if (largestunsignedint != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs no regs preserved success case  - dg_localsregsused changed\n");
        return;
    }
 

    // localsregs[0] only success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthentercallsubsframecomma(&BHarrayhead);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[0]); // reg)

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        1); // regmask of locals regs to preserve

    dg_compilemovbracketrbpd8toreg(
        &BHarrayhead,
        dg_rax,
        -0x28); 

    dg_forthexitframecomma(&BHarrayhead); 

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[1] only success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_forthentercallsubsframecomma(&BHarrayhead);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        2); // regmask of locals regs to preserve

    dg_compilemovbracketrbpd8toreg(
        &BHarrayhead,
        dg_rax,
        -0x28); 

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_forthexitframecomma(&BHarrayhead); 

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[0] only success case
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthentercallsubsframecomma(&BHarrayhead);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[0]); // reg)

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        1); // regmask of locals regs to preserve

    dg_compilemovbracketrbpd8toreg(
        &BHarrayhead,
        dg_rax,
        -0x28);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[0] only success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[1] and localsregs[3] success case a
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case a  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_forthentercallsubsframecomma(&BHarrayhead);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x98743532, // n,
        dg_localsregs[3]); // reg)

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        0x0a); // regmask of locals regs to preserve

    dg_compilemovbracketrbpd8toreg(
        &BHarrayhead,
        dg_rax,
        -0x28);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x98743532)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x98743532);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    // localsregs[1] and localsregs[3] success case b
    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case b  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x98743532, // n,
        dg_localsregs[3]); // reg)

    dg_forthentercallsubsframecomma(&BHarrayhead);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x21981387, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x98743532, // n,
        dg_localsregs[3]); // reg)

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        0x0a); // regmask of locals regs to preserve

    dg_compilemovbracketrbpd8toreg(
        &BHarrayhead,
        dg_rax,
        -0x30);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x21981387)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs localsregs[1] and localsregs[3] success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x21981387);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}
*/

void testdg_compileunpreservelocalsregsfromret()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileunpreservelocalsregsfromret\n");

    // no regs restored success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret no regs restored success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        0, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret no regs restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    if (mystartoffset != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret no regs restored success case  - code buffer length changed\n");
        return;
    }


    // localsregs[0] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] only restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[0]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        1, // localsregsmasktopreserve,
        1, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] only restored success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        2, // localsregsmasktopreserve,
        2, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[2] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[2] only restored success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        4, // localsregsmasktopreserve,
        4, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[2] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[2] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[2] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[2] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case a

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        7, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x645789)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x645789);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case a

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        7, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case c

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        7, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[0] localsregs[1] localsregs[2] restored success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x28346324);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] localsregs[3] restored success case a

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        0x0E, // localsregsmasktopreserve,
        0x0E, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[3],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x28346324);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] localsregs[3] restored success case b

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        0x0E, // localsregsmasktopreserve,
        0x0E, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] localsregs[3] restored success case c

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromret (
        &BHarrayhead,
        0x0E, // localsregsmasktopreserve,
        0x0E, // localsregsmaskallocated)
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromret localsregs[1] localsregs[3] restored success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compileunpreservenoframeregs()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileunpreservenoframeregs\n");

    // no regs restored success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - error setting dg_subroutineregspreserved\n");
        return;
    }

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - error doing dg_compileunpreservenoframeregs\n");
        return;
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    if (mystartoffset != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs no regs restored success case  - code buffer length changed\n");
        return;
    }


    // localsregs[0] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[0]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
       &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        2);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        2);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[2] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x8);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[2] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case a

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x645789)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x645789);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case b

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case c

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x18);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x28346324);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] localsregs[3] restored success case a

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        2);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        2);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0x0A);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        0x0A);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[3],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x28346324);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] localsregs[3] restored success case b

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        2);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        2);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0x0A);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b  - error setting dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        0x0A);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[1] localsregs[3] restored success case c

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[3]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[1]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_rax); // reg)

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c  - error setting dg_returnstackdepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        2);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c  - error setting dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0x0A);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c  - error setting dg_subroutineregspreserved\n");
        return;
    }


    dg_compileunpreservenoframeregs (
        &BHarrayhead,
        0x0A);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_compileaddn8torsp(
        &BHarrayhead,
        0x10);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[3]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservenoframeregs localsregs[1] localsregs[3] restored success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}



void testdg_compilebracketrbpdtodatastack()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(Bufferhandle*);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilebracketrbpdtodatastack\n");

    // [rbp-0xa0]->datastack success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case  - error compiling enter frame\n");
        return;
    }

    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0x10); // adds -0x80 to the already -0x20

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrbpd (
        &BHarrayhead,
        dg_rax,
    	-0xA0);

    dg_compilebracketrbpdtodatastack (
    	&BHarrayhead,
        -0xA0); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(&BHarrayhead);

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case b - error compiling enter frame\n");
        return;
    }

    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0x1); // adds -0x8 to the already -0x20

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrbpd (
        &BHarrayhead,
        dg_rax,
    	-0x28);

    dg_compilebracketrbpdtodatastack (
    	&BHarrayhead,
        -0x28); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case b - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct(&BHarrayhead);

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilemovbracketrbpdtoreg success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case c - error compiling enter frame\n");
        return;
    }

    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0x0C); // adds -0x60 to the already -0x20

    dg_compilemovntoreg(
        &BHarrayhead,
        0x178326, // n,
        (UINT64)dg_rax); // reg)

    dg_compilemovregtobracketrbpd (
        &BHarrayhead,
        dg_rax,
    	-0x80);

    dg_compilebracketrbpdtodatastack (
    	&BHarrayhead,
        -0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case c - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct(&BHarrayhead);

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketrbpdtodatastack success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // could test out of range + or -....

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compileunpreservelocalsregsfromframe()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileunpreservelocalsregsfromframe\n");

    // no regs restored success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe no regs restored success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileunpreservelocalsregsfromframe (
        &BHarrayhead,
        0, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe no regs restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    x = mystartoffset;

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    if (mystartoffset != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe no regs restored success case  - code buffer length changed\n");
        return;
    }


    // localsregs[0] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] only restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        1 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[0]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrsp (
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromframe (
        &BHarrayhead,
        1, // localsregsmasktopreserve,
        1, // localsregsmaskallocated)
        -1); // offset to base of frame

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[2] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[2] only restored success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        1 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrsp (
        &BHarrayhead,
        dg_rax);

    dg_compileunpreservelocalsregsfromframe (
        &BHarrayhead,
        4, // localsregsmasktopreserve,
        4, // localsregsmaskallocated)
        -1); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[2] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[2] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[2] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[2] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case a

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] localsregs[1] localsregs[2] restored success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        3 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        2 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        1 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        0 * sizeof(INT64));

    dg_compileunpreservelocalsregsfromframe (
        &BHarrayhead,
        7, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        -3); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] localsregs[1] localsregs[2] restored success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x645789)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x645789);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case b

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] localsregs[1] localsregs[2] restored success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        3 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        2 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        1 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        0 * sizeof(INT64));

    dg_compileunpreservelocalsregsfromframe (
        &BHarrayhead,
        7, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        -3); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] localsregs[1] localsregs[2] restored success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case c

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] localsregs[1] localsregs[2] restored success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        3 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        2 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        1 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        0 * sizeof(INT64));

    dg_compileunpreservelocalsregsfromframe (
        &BHarrayhead,
        7, // localsregsmasktopreserve,
        7, // localsregsmaskallocated)
        -3); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregsfromframe localsregs[0] localsregs[1] localsregs[2] restored success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservelocalsregstoframe localsregs[0] localsregs[1] localsregs[2] restored success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x28346324);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // structure of the code is exactly the same as dg_compileunpreservelocalsregstoret
    //   so I'm going to skip further tests...


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compileunpreservecallsubsframeregs()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileunpreservecallsubsframeregs\n");

    // no regs restored success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs no regs restored success case  - could not initialize dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs no regs restored success case  - could not initialize dg_subroutineregspreserved\n");
        return;
    }

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs no regs restored success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileunpreservecallsubsframeregs (
        &BHarrayhead,
        0);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs no regs restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    x = mystartoffset;

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs no regs restored success case  - could not get current compile buffer's length\n");
        return;
    }

    if (mystartoffset != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs no regs restored success case  - code buffer length changed\n");
        return;
    }


    // localsregs[0] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] only restored success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        1 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[0]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrsp (
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] only restored success case  - could not initialize dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] only restored success case  - could not initialize dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservecallsubsframeregs (
        &BHarrayhead,
        1); // offset to base of frame

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[2] only restored success case

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[2] only restored success case - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        1 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrsp (
        &BHarrayhead,
        dg_rax);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        1);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[2] only restored success case  - could not initialize dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[2] only restored success case  - could not initialize dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservecallsubsframeregs (
        &BHarrayhead,
        4); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[2] only restored success case  - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[2] only restored success case - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[2] only restored success case - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[2] only restored success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x3845621);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case a

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        3 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        2 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        1 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        0 * sizeof(INT64));

    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a  - could not initialize dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a  - could not initialize dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservecallsubsframeregs (
        &BHarrayhead,
        7); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[0],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x645789)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case a - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x645789);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case b

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        3 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        2 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        1 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        0 * sizeof(INT64));

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b  - could not initialize dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b  - could not initialize dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservecallsubsframeregs (
        &BHarrayhead,
        7); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[1],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x8946354)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x8946354);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    // localsregs[0] localsregs[1] localsregs[2] restored success case c

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepushregtoret( 
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthenterrbpframecomma(&BHarrayhead);

    dg_compilesubn8fromrsp(
        &BHarrayhead,
        3 * sizeof(UINT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0, // n,
        dg_localsregs[2]); // reg)

    dg_compilemovntoreg(
        &BHarrayhead,
        0x28346324, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        2 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x8946354, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        1 * sizeof(INT64));

    dg_compilemovntoreg(
        &BHarrayhead,
        0x645789, // n,
        dg_rax); // reg)

    dg_compilemovregtobracketrspd8 (
        &BHarrayhead,
        dg_rax,
        0 * sizeof(INT64));

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        3);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c  - could not initialize dg_regspreserveddepth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        7);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c  - could not initialize dg_subroutineregspreserved\n");
        return;
    }

    dg_compileunpreservecallsubsframeregs (
        &BHarrayhead,
        7); 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compileunpreservecallsubsframeregs (
        &BHarrayhead,
        7); // offset to base of frame = -1 * numberofbitspreserved

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - error doing dg_compilepreservelocalsregstoret\n");
        return;
    }

    dg_compilemovregtoreg(
        &BHarrayhead,
        dg_localsregs[2],
        dg_rax);

    dg_forthexitframecomma(&BHarrayhead);
    
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[2]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x28346324)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileunpreservecallsubsframeregs localsregs[0] localsregs[1] localsregs[2] restored success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x28346324);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        x = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

        dg_hexdumpsegment (
            &BHarrayhead,
            (unsigned char*)pfunct,
            x - mystartoffset);

        return;
    }


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compiledatastacktobracketrbpd()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(Bufferhandle*);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compiledatastacktobracketrbpd\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case  - error compiling enter frame\n");
        return;
    }

    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0x10); // adds -0x80 to the already -0x20

    dg_compiledatastacktobracketrbpd (
    	&BHarrayhead,
        -0xA0); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case  - error doing dg_compiledatastacktobracketrbpd\n");
        return;
    }

    dg_compilemovbracketrbpdtoreg (
        &BHarrayhead,
        dg_rax,
    	-0xA0);

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case  - error compiling test routine\n");
        return;
    }

    dg_pushdatastack(&BHarrayhead, 0x178326);

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(&BHarrayhead);

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case b - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case b - error compiling enter frame\n");
        return;
    }

    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0x1); // adds -0x8 to the already -0x20

    dg_compiledatastacktobracketrbpd (
    	&BHarrayhead,
        -0x28); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case b - error doing dg_compiledatastacktobracketrbpd\n");
        return;
    }

    dg_compilemovbracketrbpdtoreg (
        &BHarrayhead,
        dg_rax,
    	-0x28);

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case b - error compiling test routine\n");
        return;
    }

    dg_pushdatastack(&BHarrayhead, 0x178326);

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct(&BHarrayhead);

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case b - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case c - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case c - error compiling enter frame\n");
        return;
    }

    dg_compileaddnlocalstocallsubsframe (
        &BHarrayhead,
        0x0C); // adds -0x60 to the already -0x20

    dg_compiledatastacktobracketrbpd (
    	&BHarrayhead,
        -0x80); // displacement) (32 bit so should be ok with -value)

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case c - error doing dg_compiledatastacktobracketrbpd\n");
        return;
    }

    dg_compilemovbracketrbpdtoreg (
        &BHarrayhead,
        dg_rax,
    	-0x80);

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case c - error compiling test routine\n");
        return;
    }

    dg_pushdatastack(&BHarrayhead, 0x178326);

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case c - error getting start address of test function\n");
        return;
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x178326)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compiledatastacktobracketrbpd success case c - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // could test out of range + or -....

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilecallcoreoneuparam()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(Bufferhandle*);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilecallcoreoneuparam\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoreoneuparam success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoreoneuparam success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoreoneuparam success case  - error compiling enter frame\n");
        return;
    }

    dg_compilecallcoreoneuparam (
        &BHarrayhead, 
        (UINT64)&dg_pushdatastack, // addr,
        0x8347283937);     // uparam1)

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoreoneuparam success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoreoneuparam success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(&BHarrayhead);

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x8347283937)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoreoneuparam success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_compilecallcoretwouparams()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)(Bufferhandle*);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilecallcoretwouparams\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoretwouparams success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoretwouparams success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compileinitlocals(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoretwouparams success case  - error compiling enter frame\n");
        return;
    }

    dg_compilecallcoretwouparams (
        &BHarrayhead, 
        (UINT64)&dg_pushbufferuint64, // addr,
        DG_DATASTACK_BUFFERID,
        0x8347283937);     // uparam2)

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoretwouparams success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)(Bufferhandle*))dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoretwouparams success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct(&BHarrayhead);

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x8347283937)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilecallcoretwouparams success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x178326);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


/*
void testdg_compilebracketobtoptodatastack()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilebracketobtodatastack\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketobtodatastack success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketobtodatastack success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        (UINT64)&BHarrayhead,
        dg_param1reg);

    dg_compileinitlocals(&BHarrayhead);

    dg_compilemovntoreg(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_param2reg);

    dg_compilemovntoreg(
        &BHarrayhead,
        currentcompilebuffer,
        dg_param3reg);

    dg_compilebracketobtodatastack (
    	&BHarrayhead,
    	DG_DATASPACE_BUFFERID,
    	currentcompilebuffer);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x1122554477,
        dg_rax);

    dg_compileexitlocals(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketobtodatastack success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketobtodatastack success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x1122554477)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketobtodatastack success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x1122554477);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != mycurrentcompilebuffer)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilebracketobtodatastack success case - data stack not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}
*/


void testdg_compileopreg64tobracketrsp()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compileopreg64tobracketrsp\n");

    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax add success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax add success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax add success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        3,
        dg_rax);

    dg_compilepushregtoret (
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0802030405060701, // n,
        dg_rax); // reg)

    dg_compileopreg64tobracketrsp (
        &BHarrayhead,
        dg_rax,
        0x01); // add r -> m

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax add success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax add success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax add success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x0802030405060704)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax add success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x0802030405060704);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rcx add success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rcx add success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rcx add success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        3,
        dg_rcx);

    dg_compilepushregtoret (
        &BHarrayhead,
        dg_rcx);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0802030405060701, // n,
        dg_rcx); // reg)

    dg_compileopreg64tobracketrsp (
        &BHarrayhead,
        dg_rcx,
        0x01); // add r -> m

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rcx add success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rcx add success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rcx add success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x0802030405060704)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rcx add success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x0802030405060704);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax sub success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax sub success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax sub success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0802030405060709,
        dg_rax);

    dg_compilepushregtoret (
        &BHarrayhead,
        dg_rax);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0802030405060701, // n,
        dg_rax); // reg)

    dg_compileopreg64tobracketrsp (
        &BHarrayhead,
        dg_rax,
        (0x05 << 3) | 1); // sub r -> m

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax sub success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax sub success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax sub success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x08)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp rax sub success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x08);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp r9 add success case  - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp r9 add success case  - could not get current compile buffer's length\n");
        return;
    }

    dg_forthenterrbpframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp r9 add success case  - error compiling enter frame\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        4,
        dg_r9);

    dg_compilepushregtoret (
        &BHarrayhead,
        dg_r9);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x0802030405060701, // n,
        dg_r9); // reg)

    dg_compileopreg64tobracketrsp (
        &BHarrayhead,
        dg_r9,
        0x01); // add r -> m

    dg_compilepopregfromret( 
        &BHarrayhead,
        dg_rax);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp r9 add success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp r9 add success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp r9 add success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x0802030405060705)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compileopreg64tobracketrsp r9 add success case - return not correct, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x0802030405060705);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");
}


void testdg_compilepreservecallsubsregs ()
{
    Bufferhandle BHarrayhead;

    // Bufferhandle* pBH;

    UINT64 mycurrentcompilebuffer = 0;
    UINT64 mystartoffset = 0;
    UINT64 x;

    UINT64(*pfunct)();

    dg_initpbharrayhead(&BHarrayhead);
   
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_compilepreservecallsubsregs\n");

    // preserving 0 success case   
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case - could not get current compile buffer's length\n");
        return;
    }

    dg_forthentercallsubsframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case - error compiling enter frame\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case - could not set return stack depth to 0\n");
        return;
    }

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        0); // localsregsmask);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (x != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case - return stack depth changed, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 4);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_forthexitframecomma(&BHarrayhead);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 0 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    // crash test... nothing should change...

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    // preserving 1 success case   
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case - could not get current compile buffer's length\n");
        return;
    }

    // just in case it is a must be preserved reg .. not part of frame
    dg_compilepushregtoret (
        &BHarrayhead,
        dg_localsregs[0]);

    dg_forthentercallsubsframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case - error compiling enter frame\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case - could not set return stack depth to 0\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x78287634,
        dg_localsregs[0]);

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        1); // localsregsmask);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case  - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovbracketrbpd8toreg (
        &BHarrayhead,
        dg_rax,
        (-5) * sizeof(INT64)); // displacement8)

    dg_forthexitframecomma(&BHarrayhead);

    // restoring localsreg[0] just in case it had to be preserved
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case  - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case  - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x78287634)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case - return stack depth changed, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x78287634);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (x != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 1 success case - return stack depth changed, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 5);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    // preserving 2 success case a
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - could not get current compile buffer's length\n");
        return;
    }

    // just in case it is a must be preserved reg .. not part of frame
    dg_compilepushregtoret (
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilepushregtoret (
        &BHarrayhead,
        dg_localsregs[1]);

    dg_forthentercallsubsframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - error compiling enter frame\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - could not set return stack depth to 0\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x78287634,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x9827347,
        dg_localsregs[1]);

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        3); // localsregsmask);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovbracketrbpd8toreg (
        &BHarrayhead,
        dg_rax,
        (-5) * sizeof(INT64)); // displacement8)

    dg_forthexitframecomma(&BHarrayhead);

    // restoring localsreg[0] and localsreg[1] just in case it had to be preserved
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x9827347)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - return stack depth changed, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x9827347);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (x != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case a - return stack depth changed, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 6);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    // preserving 2 success case b
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - could not get current compile buffer\n");
        return;
    }

    mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - could not get current compile buffer's length\n");
        return;
    }

    // just in case it is a must be preserved reg .. not part of frame
    dg_compilepushregtoret (
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilepushregtoret (
        &BHarrayhead,
        dg_localsregs[1]);

    dg_forthentercallsubsframecomma(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - error compiling enter frame\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth,
        4);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - could not set return stack depth to 0\n");
        return;
    }

    dg_compilemovntoreg(
        &BHarrayhead,
        0x78287634,
        dg_localsregs[0]);

    dg_compilemovntoreg(
        &BHarrayhead,
        0x9827347,
        dg_localsregs[1]);

    dg_compilepreservecallsubsregs (
        &BHarrayhead,
        3); // localsregsmask);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - error doing dg_compilemovbracketrbpdtoreg\n");
        return;
    }

    dg_compilemovbracketrbpd8toreg (
        &BHarrayhead,
        dg_rax,
        (-6) * sizeof(INT64)); // displacement8)

    dg_forthexitframecomma(&BHarrayhead);

    // restoring localsreg[0] and localsreg[1] just in case it had to be preserved
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[1]);

    dg_compilepopregfromret(
        &BHarrayhead,
        dg_localsregs[0]);

    dg_compilereturn(&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - error compiling test routine\n");
        return;
    }

    pfunct = (UINT64(*)())dg_getpbufferoffset(
        &BHarrayhead,
        mycurrentcompilebuffer,
        mystartoffset);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - error getting start address of test function\n");
        return;
    }

    x = pfunct();

    if (x != 0x78287634)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - return stack depth changed, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x78287634);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_returnstackdepth);

    if (x != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_compilepreservecallsubsregs preserving 2 success case b - return stack depth changed, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 6);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    dg_printzerostring(&BHarrayhead, (unsigned char*)"  ... test done\n");
}


void testdg_getcallsubsframepreservedregoffset ()
{
    Bufferhandle BHarrayhead;

    INT64 offset;


    dg_initpbharrayhead(&BHarrayhead);
   
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getcallsubsframepreservedregoffset\n");

    
    //  getting offset of first of 4 preserved success case   
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        8);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset first of four case error putting preserved depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0x2148);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset first of four case error putting preserved mask\n");
        return;
    }
    
    offset = dg_getcallsubsframepreservedregoffset(
        &BHarrayhead,
        3); // position of first set bit 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset first of four case error doing dg_getcallsubsframepreservedregoffset \n");
        return;
    }

    if (offset != -8 * sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - first of four case got wrong depth, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)-0x40);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)offset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    //  getting offset of second of 4 preserved success case   
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        8);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset second of four case error putting preserved depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0x2148);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset second of four case error putting preserved mask\n");
        return;
    }
    
    offset = dg_getcallsubsframepreservedregoffset(
        &BHarrayhead,
        6); // position of second set bit 

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset second of four case error doing dg_getcallsubsframepreservedregoffset\n");
        return;
    }

    if (offset != -7 * sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - second of four case got wrong depth, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)-0x38);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)offset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    //  getting offset of third of 4 preserved success case   
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        8);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - third of four case error putting preserved depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0x2148);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - third of four case error putting preserved mask\n");
        return;
    }
    
    offset = dg_getcallsubsframepreservedregoffset(
        &BHarrayhead,
        8); // position of third set bit

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - third of four case error doing dg_getcallsubsframepreservedregoffset \n");
        return;
    }

    if (offset != -6 * sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - third of four case got wrong depth, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)-0x30);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)offset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);


    //  getting offset of fourth of 4 preserved success case   
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_regspreserveddepth,
        8);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - fourth of four case error putting preserved depth\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_subroutineregspreserved,
        0x2148);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - fourth of four case error putting preserved mask\n");
        return;
    }
    
    offset = dg_getcallsubsframepreservedregoffset(
        &BHarrayhead,
        13); // position of fourth set bit

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - fourth of four case error doing dg_getcallsubsframepreservedregoffset \n");
        return;
    }

    if (offset != -5 * sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getcallsubsframepreservedregoffset - fourth of four case got wrong depth, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)-0x28);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)offset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


// probably good idea to test the whole frame...
//   enterframe declareparameters preserveregs useregs declarelocals unpreserveregs exitframe...

// test frame preserve and unpreserve for freg with >=0x80 displacement thoroughly...
//   make sure regs are really being preserved and unpreserved from correct spot
// test preserve and unpreserve with case that causes crash...
//   which is with all 18 windows must be preserved registers
//   make sure each register is left unchanged...

// finally change U-MUST-BE-PRESERVED... split it up into U-IMUST-BE-PRESERVED and U-FMUST-BE-PRESERVED...
