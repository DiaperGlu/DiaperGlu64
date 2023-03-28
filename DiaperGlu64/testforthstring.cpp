// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.8.
//
//    DiaperGlu v5.8 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.8 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.8; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// March 27, 2023             //
// version 5.8                //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"

void testdg_forthdashtrailing ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    void* pbuf = (void*)"asd   ";
    
    UINT64 x;
    
    const char* pError;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing -TRAILING\n");
    
    // success case 1
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)pbuf);
    dg_pushdatastack(&BHarrayhead, 6);
    
    dg_forthdashtrailing(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdashtrailing success case - expected no error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdashtrailing success case - got wrong length on top of data stack\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != (UINT64)pbuf)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdashtrailing success case - got wrong address one below top of data stack\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
        
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdashtrailing success case - data stack not empty after test\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthslashstring ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    
    const char* pError;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing /STRING\n");
    
    // success case 1
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, 100);
    dg_pushdatastack(&BHarrayhead, 5);
    
    dg_pushdatastack(&BHarrayhead, 2);
    
    dg_forthslashstring(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - expected no error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - got wrong length on top of data stack\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 102)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - got wrong address one below top of data stack\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
        
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - data stack not empty after test\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success case 2
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, 100);
    dg_pushdatastack(&BHarrayhead, 5);
    
    dg_pushdatastack(&BHarrayhead, 6);
    
    dg_forthslashstring(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - expected no error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - got wrong length on top of data stack\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 105)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - got wrong address one below top of data stack\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
        
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - data stack not empty after test\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 3
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, 100);
    dg_pushdatastack(&BHarrayhead, 5);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)-6);
    
    dg_forthslashstring(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - expected no error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - got wrong length on top of data stack\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 94)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - got wrong address one below top of data stack\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
        
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslashstring success case - data stack not empty after test\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthblank ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    const char* pError;
    
    unsigned char caddr1[8];
    caddr1[0] = 'a';
    caddr1[1] = 'b';
    caddr1[2] = 'c';
    caddr1[3] = 'd';
    caddr1[4] = 'e';
    caddr1[5] = 'f';
    caddr1[6] = 'g';
    caddr1[7] = 'h'; 
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing BLANK\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)(caddr1 + 1));
    dg_pushdatastack(&BHarrayhead, 3);
    
    dg_forthblank(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        // pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthblank success case - expected no error, got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (caddr1[0] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthblank success case - got wrong character before change\n");
    }
    
    if (caddr1[1] != ' ')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthblank success case - got wrong 1st changed character\n");
    }
    
    if (caddr1[2] != ' ')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthblank success case - got wrong 2nd changed character\n");
    }
    
    if (caddr1[3] != ' ')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthblank success case - got wrong 3rd changed character\n");
    }
    
    if (caddr1[4] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthblank success case - got wrong character after change\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthcompare ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    unsigned char* caddr1 = (unsigned char*)"abcdefg";
    unsigned char* caddr2 = (unsigned char*)"abc";
    UINT64 u1 = 7;
    UINT64 u2 = 3;
    
    UINT64 x;
    
    const char* pError;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing COMPARE\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)caddr1);
    dg_pushdatastack(&BHarrayhead, u1);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)caddr2);
    dg_pushdatastack(&BHarrayhead, u2);
    
    dg_forthcompare(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcompare success case - expected no error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcompare success case - got wrong result on top of data stack\n");
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
        
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcompare success case - data stack not empty after test\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthsearch ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    unsigned char* caddr1 = (unsigned char*)"abcdefg";
    unsigned char* caddr2 = (unsigned char*)"def";
    UINT64 u1 = 7;
    UINT64 u2 = 3;
    
    UINT64 x;
    
    const char* pError;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing SEARCH\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)caddr1);
    dg_pushdatastack(&BHarrayhead, u1);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)caddr2);
    dg_pushdatastack(&BHarrayhead, u2);
    
    dg_forthsearch(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearch success case - expected no error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearch success case - got wrong result on top of data stack\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearch success case - got wrong result 1 below top of data stack\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != (UINT64)(caddr1 + 3))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearch success case - got wrong result 2 below top of data stack\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // bad memory case
    dg_initbuffers(&BHarrayhead);
    
    dg_clearerrors(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)-1);
    dg_pushdatastack(&BHarrayhead, u1);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)caddr2);
    dg_pushdatastack(&BHarrayhead, u2);
    
    dg_forthsearch(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthsearchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearch bad memory case - got wrong error on top. expected dg_forthsearchname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_searchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearch bad memory case - got wrong error 1 below top. expected dg_searchname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearch bad memory case - got wrong error 2 below top. expected dg_badmemoryerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    // test error getting pointer to datastack
    // test data stack underflow
    // test not found
}


void testdg_forthcomparestring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	UINT64* plength = NULL;
	UINT64* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthcomparestring\n");
#ifndef DGLU_NO_DIAPER
	// error getting number of strings on string stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthcomparestring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcomparestringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring error getting number of strings on string stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring error getting number of strings on string stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// string stackunderflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthcomparestring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcomparestringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to lstring 1 away from top
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthcomparestring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcomparestringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring error getting pointer to lstring 1 away from top case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring error getting pointer to lstring 1 away from top case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to lstring on top
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	pbuffer = (UINT64*)dg_getpbuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, &plength);

	testint = pbuffer[0];
	pbuffer[0] = pbuffer[1];
	pbuffer[1] = testint;

	dg_forthcomparestring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcomparestringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring error getting pointer to lstring on top case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcomparestring error getting pointer to lstring on top case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// error pushing flag
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthcomparestring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcomparestringname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring error pushing flag case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring error pushing flag case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring error pushing flag case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthcomparestring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 1 - expected 'cat' < 'dogs'\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 1 - data  stack not balanced after calculation\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthcomparestring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 2 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 2 - expected 'dogs' > 'cats'\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 2 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 3
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthcomparestring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 3 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 3 - expected 'cat' = 'cat'\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 3 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 4
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"cats");

	dg_forthcomparestring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 4 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 4 - expected 'cat' < 'cats'\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 4 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 5
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"cats");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthcomparestring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 5 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 5 - expected 'cats' > 'cat'\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 5 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 6
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"catsy");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"catmandu");

	dg_forthcomparestring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 6 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 6 - expected 'catsy' > 'catmandu'\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_forthcomparestring success case 6 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthgetmidstring ()
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

	Bufferhandle* pBH = NULL;

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetmidstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to data stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthgetmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	//  data stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8340);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	
	dg_forthgetmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring data stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring data stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting number of strings on string stack
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthgetmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error getting number of strings on string stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error getting number of strings on string stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// string stack underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthgetmidstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring string stack underflow case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring string stack underflow case case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// if getnumberoflstringsworked and there is no string stack underflow,
	//  I don't know how to get an error getting the start offset or the length of the top string


	// length too long case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthgetmidstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring length too long case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsegmentgoespastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring length too long case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// offset too long case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthgetmidstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring offset too long case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsegmentgoespastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring offset too long case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


	// error growing string buffer case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_STRINGSTRINGSTACK_BUFFERID] );

	pBH->size    = pBH->nextunusedbyte;
	pBH->maxsize = pBH->nextunusedbyte;
	pBH->growby  = pBH->nextunusedbyte;

	dg_forthgetmidstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error growing string buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error growing string buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// error pushing new end offset case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_STRINGOFFSETSTACK_BUFFERID] );

	pBH->size    = pBH->nextunusedbyte;
	pBH->maxsize = pBH->nextunusedbyte;
	pBH->growby  = pBH->nextunusedbyte;

	dg_forthgetmidstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error pushing new end offset case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error pushing new end offset case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring error pushing new end offset case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// if grow string stack's string buffer worked, don't know how to get an error getting pointer to string stack's string buffer
#endif

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthgetmidstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - error count not 0 \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - 2 strings not on stack \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 6)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string stack's string buffer length not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 3);

	if (testint != (UINT64)'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 1 char 0 not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 4);

	if (testint != (UINT64)'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 1 char 1 not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 5);

	if (testint != (UINT64)'t')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 1 char 1 not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 0);

	if (testint != (UINT64)'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 0 char 0 not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 1);

	if (testint != (UINT64)'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 0 char 1 not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 2);

	if (testint != (UINT64)'t')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 0 char 1 not what was expected \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 0's end offset not what was expected \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 6)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string 1's end offset not what was expected \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - string offset stack's length not what was expected, \n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 6, (unsigned char*)"dogmis");

	dg_forthgetmidstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - error count not 0 \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - 2 strings not on stack \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string stack's string buffer length not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 9);

	if (testint != (UINT64)'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string 1 char 0 not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 10);

	if (testint != (UINT64)'m')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string 1 char 1 not what was expected \n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 11);

	if (testint != (UINT64)'i')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string 1 char 1 not what was expected \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string 0's end offset not what was expected \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string 1's end offset not what was expected \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string 2's end offset not what was expected \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - string offset stack's length not what was expected, \n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetmidstring success case 2 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// would be nice to check the cases where the offset and string buffers move
	//  but windows doesn't have a way to for sure force an address change...
	//  maybe I could add that to grow buffer... always force move hmmm
}


void testdg_forthcatstring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthcatstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to string stack's offset stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthcatstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcatstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring error getting pointer to string stack's offset stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring error getting pointer to string stack's offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring error getting pointer to string stack's offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	//  string stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	
	dg_forthcatstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcatstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring string stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring string stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");
	
	dg_forthcatstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring success case 1 - error count not 0 \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring success case 2 - string 0's end offset not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcatstring success case 2 - string offset stack's length not what was expected, \n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthlengthstring()
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

	const char* pError = NULL;
	UINT64 testint = 0;
	UINT64 t2 = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlengthstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting number of strings on string stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthlengthstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlengthstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring error getting number of strings on string stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring error getting number of strings on string stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	//  string stack underflow
	dg_initbuffers(&BHarrayhead);
	
	dg_forthlengthstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlengthstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring string stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring string stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting length of top string
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	testint = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);
	t2 = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, testint);
	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, t2);

	dg_forthlengthstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlengthstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring error getting length of top string case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getlstringlengthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring error getting length of top string case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing data stack
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthlengthstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlengthstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring error pushing data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring error pushing data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring error pushing data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");
	
	dg_forthlengthstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring success case 1 - top string's length not what was expected, \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring success case 1 - string 0's end offset not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthstring success case 1 - string offset stack's length not what was expected, \n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthshortenstring()
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

	const char* pError = NULL;
	UINT64 testint = 0;
	UINT64 t2 = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthshortenstring\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthshortenstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthshortenstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting pointer to string offset stack
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);
	
	dg_forthshortenstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthshortenstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error getting pointer to string offset stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error getting pointer to string offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error getting pointer to string offset stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	
	dg_forthshortenstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthshortenstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// corrupt offset stack error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	testint = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);
	t2 = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, testint);
	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, t2);
	
	dg_forthshortenstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthshortenstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring corrupt offset stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringstackdepthcorrupt)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring corrupt offset stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error shrinking string buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);
	
	dg_forthshortenstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthshortenstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error shrinking string buffer - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_shrinkbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring error shrinking string buffer - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	
	dg_forthshortenstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 1 - error count not 0 \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 1 - string 0's end offset not what was expected, \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 1 - string 1's end offset not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 1 - string offset stack's length not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 1 - string string stack's length not what was expected, \n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	
	dg_forthshortenstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 2 - error count not 0 \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 2 - string 0's end offset not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 2 - string offset stack's length not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthshortenstring success case 2 - string string stack's length not what was expected, \n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthpickstring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthpickstring\n");
#ifndef DGLU_NO_DIAPER

	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthpickstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpickstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error picking string
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthpickstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpickstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring error picking string case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_picklstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring error picking string case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	
	dg_forthpickstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - error count not 0 \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string 0's end offset not what was expected, \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string 1's end offset not what was expected, \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 13)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string 1's end offset not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string offset stack's length not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 13)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string string stack's length not what was expected, \n");
	}

	testint = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 10);

	if (testint != (UINT64)'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string 2 char 0 not what was expected, \n");
	}

	testint = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 11);

	if (testint != (UINT64)'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string 2 char 1 not what was expected, \n");
	}

	testint = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 12);

	if (testint != (UINT64)'t')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - string 2 char 2 not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 1 - data stack not balanced after test, \n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	dg_forthpickstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - error count not 0 \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string 0's end offset not what was expected, \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string 1's end offset not what was expected, \n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 13)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string 2's end offset not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string offset stack's length not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 13)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string string stack's length not what was expected, \n");
	}

	testint = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 10);

	if (testint != (UINT64)'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string 2 char 0 not what was expected, \n");
	}

	testint = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 11);

	if (testint != (UINT64)'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string 2 char 1 not what was expected, \n");
	}

	testint = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 12);

	if (testint != (UINT64)'t')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - string 2 char 2 not what was expected, \n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpickstring success case 2 - data stack not balanced after test, \n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// would be nice to test the case where the buffers move when grown
}


void testdg_forthdropstring ()
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

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdropstring\n");
#ifndef DGLU_NO_DIAPER

	// error doing dg_droplstring
	dg_initbuffers(&BHarrayhead);

	dg_forthdropstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdropstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring error doing droplstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_droplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring error doing droplstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 and 2
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	
	dg_forthdropstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring success case 1 - number of strings on stack not what expected\n");
	}

	dg_forthdropstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring success case 2 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring success case 2 - number of strings on stack not what expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdeletestring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdeletestring\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthdeletestring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeletestringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletestring error doing dg_droplstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletestring error doing dg_droplstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletestring error doing dg_droplstring case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error doing dg_deletelstring
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthdeletestring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeletestringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletestring error doing dg_droplstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_deletelstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletestring error doing dg_droplstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	dg_forthdeletestring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdropstring success case 1 - end of string 0 offset not what expected\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthswapstring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthswapstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting number of strings
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthswapstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthswapstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring error getting number of strings case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring error getting number of strings case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthswapstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthswapstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error doing overstring
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthswapstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthswapstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring error doing overstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthoverstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring error doing overstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// not sure how to get the delete string error if over string worked
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	dg_forthswapstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - end of string 0 offset not what expected\n");
	}
	
	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 0);

	if (testint != (UINT64)'z')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - string 0 char 0 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 1);

	if (testint != (UINT64)'e')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - string 0 char 1 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 2);

	if (testint != (UINT64)'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - string 1 char 0 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 3);

	if (testint != (UINT64)'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - string 1 char 1 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 4);

	if (testint != (UINT64)'t')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthswapstring success case 1 - string 1 char 2 not what expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthnipstring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnipstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting number of strings
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthnipstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnipstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring error getting number of strings case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring error getting number of strings case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthnipstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnipstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error doing dg_deletelstring
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthnipstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnipstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring error doing dg_forthdeletestring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_deletelstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring error doing dg_forthdeletestring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	dg_forthnipstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring success case 1 - end of string 0 offset not what expected\n");
	}
	
	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 0);

	if (testint != (UINT64)'z')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring success case 1 - string 0 char 0 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 1);

	if (testint != (UINT64)'e')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnipstring success case 1 - string 0 char 1 not what expected\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthrotstring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthrotstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting number of strings
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthrotstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrotstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring error getting number of strings case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring error getting number of strings case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthrotstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrotstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error doing dg_picklstring
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"doggies");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"puny");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthrotstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrotstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring error doing dg_picklstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_picklstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring error doing dg_picklstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// not sure how to get the dg_deletelstring error if dg_picklstring worked
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	dg_forthrotstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 6)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - end of string 0 offset not what expected\n");
	}

	
	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 0);

	if (testint != (UINT64)'z')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 0 char 0 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 1);

	if (testint != (UINT64)'e')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 0 char 1 not what expected\n");
	}
	

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 2);

	if (testint != (UINT64)'d')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 1 char 0 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 3);

	if (testint != (UINT64)'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 1 char 1 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 4);

	if (testint != (UINT64)'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 1 char 2 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 5);

	if (testint != (UINT64)'s')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 1 char 3 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 6);

	if (testint != (UINT64)'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 2 char 0 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 7);

	if (testint != (UINT64)'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 2 char 1 not what expected\n");
	}

	testint = (UINT64)dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 8);

	if (testint != (UINT64)'t')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthrotstring success case 1 - string 2 char 2 not what expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdepthstring ()
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

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdepthstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting number of strings
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthdepthstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdepthstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring error getting number of strings case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring error getting number of strings case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error pushing to data stack
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthdepthstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdepthstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring error pushing to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring error pushing to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring error pushing to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	
	dg_forthdepthstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 1 - number of strings on stack not what expected\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 1 - data stack value not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success cases 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 44);
	
	dg_forthdepthstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 2 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 2 - number of strings on stack not what expected\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 2 - data stack value not what was expected\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 44)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 2 - data stack corrupted\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthstring success case 2 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthnewstring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnewstring\n");
#ifndef DGLU_NO_DIAPER
	// error doing dg_pushlstring
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthnewstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnewstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring error error doing dg_pushlstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring error error doing dg_pushlstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	
	dg_forthnewstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 32)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - end of string 2 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 24);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnewstring success case 1 - end of string 3 offset not what expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthchartostring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthctonewstring\n");
#ifndef DGLU_NO_DIAPER
	// error popping datastack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthctonewstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthctonewstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring error popping datastack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring error popping datastack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring error popping datastack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error doing dg_pushlstring
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 'q');

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthctonewstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthctonewstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring error error doing dg_pushlstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring error error doing dg_pushlstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (unsigned char)'q');
	
	dg_forthctonewstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 32)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - end of string 2 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 24);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - end of string 3 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 9) != 'q')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctonewstring success case 1 - string 3 char 0 not what expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthtonewstring()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthtonewstring\n");
#ifndef DGLU_NO_DIAPER
	// error popping datastack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthtonewstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtonewstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring error popping datastack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring error popping datastack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring error popping datastack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error doing dg_pushlstring
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x01020304);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthtonewstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtonewstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring error error doing dg_pushlstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring error error doing dg_pushlstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0102030405060708);
	
	dg_forthtonewstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 32)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 17)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - end of string 2 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 24);

	if (testint != 17)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - end of string 3 offset not what expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 9) != 0x0102030405060708)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtonewstring success case 1 - string 3 chars 0-7 not what expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthturnstringinto0string ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthturnstringinto0string\n");
#ifndef DGLU_NO_DIAPER

	// error doing dg_pushlstring
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 'q');

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthturnstringinto0string(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthturnstringinto0stringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string error error doing dg_pushlstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string error error doing dg_pushlstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error doing catenate string
	dg_initbuffers(&BHarrayhead);

	dg_forthturnstringinto0string(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthturnstringinto0stringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string error doing catenate string case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcatstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string error doing catenate string case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	
	dg_forthturnstringinto0string(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 8) != 's')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - string 2 char 3 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 9) != '\0')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - string 2 char 4 not what expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthinsertinstring ()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthinsertinstring\n");
#ifndef DGLU_NO_DIAPER

	// error getting pointer to the data stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthinsertinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// data stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthinsertinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring data stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring data stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting string stack depth
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthinsertinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring error getting string stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring error getting string stack depth case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthinsertinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// dont know how to get an error getting the start offset if there was no string stack underflow


	// error inserting in string buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthinsertinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring error inserting in string buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertinbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring error inserting in string buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// if insert worked I don't know how to get an error getting the string stack's string buffer length

	// if getting string stack depth worked... not sure how to get an error putting the new end offset
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	
	dg_forthinsertinstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 5) != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - string 2 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 6) != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - string 2 char 1 not what expected\n");
	}
	
	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 7) != 'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthturnstringinto0string success case 1 - string 2 char 2 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 8) != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - string 2 char 3 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 9) != 'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - string 2 char 4 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 10) != 's')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - string 2 char 5 not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertinstring success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdeleteinstring ()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdeleteinstring\n");
#ifndef DGLU_NO_DIAPER

	// error getting pointer to the data stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthdeleteinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeleteinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// data stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthdeleteinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeleteinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring data stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring data stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting string stack depth
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthdeleteinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeleteinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring error getting string stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring error getting string stack depth case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthdeleteinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeleteinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting pointer to string stack
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthdeleteinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeleteinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring error getting pointer to string stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring error getting pointer to string stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// length > stringlength
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthdeleteinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeleteinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring length > stringlength case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsegmentgoespastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring length > stringlength case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// goes off end error, offset > stringlength - length
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthdeleteinstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeleteinstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring goes off end error, offset > stringlength - length case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsegmentgoespastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring goes off end error, offset > stringlength - length case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// don't know how to get the shorten string error if the other stuff worked
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	
	dg_forthdeleteinstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 16);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 5) != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - string 2 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 6) != 's')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - string 2 char 1 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeleteinstring success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthstringcfetch ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstringcfetch\n");
#ifndef DGLU_NO_DIAPER

	// error getting pointer to the data stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthstringcfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch error getting pointer to the data stack case - got wrong error on top, got");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// data stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_forthstringcfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch data stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch data stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting string stack depth
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthstringcfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch error getting string stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch error getting string stack depth case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting pointer to top string
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthstringcfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch error getting pointer to top string case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch error getting pointer to top string case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// offset >= stringlength
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthstringcfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch offset >= stringlength case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringoffsetpastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch offset >= stringlength case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	
	dg_forthstringcfetch(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - wrong character returned, \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2*sizeof(UINT64));

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 5) != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - string 2 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 6) != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - string 2 char 1 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcfetch success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthstringcstore ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstringcstore\n");
#ifndef DGLU_NO_DIAPER

	// error getting pointer to the data stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthstringcstore(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// data stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcstore(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore data stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore data stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting string stack depth
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthstringcstore(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore error getting string stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore error getting string stack depth case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcstore(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting pointer to top string
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthstringcstore(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore error getting pointer to top string case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore error getting pointer to top string case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// offset >= stringlength
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x41);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthstringcstore(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore offset >= stringlength case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringoffsetpastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore offset >= stringlength case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)'q');
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	
	dg_forthstringcstore(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2*sizeof(UINT64));

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 5) != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - string 2 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 6) != 'q')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - string 2 char 1 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthstringtoc ()
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

	const char* pError = NULL;
	UINT64 testint = 0;
	UINT64 t2 = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstringtoc\n");
#ifndef DGLU_NO_DIAPER

	// error getting pointer to string offset stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthstringtoc(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtocname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error getting pointer to string offset stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error getting pointer to string offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error getting pointer to string offset stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_forthstringtoc(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtocname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string offset stack corrupt
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");

	testint = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);
	t2 = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, testint);
	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, t2);

	dg_forthstringtoc(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtocname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc string offset stack corrupt case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsoffsetscorruptname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc string offset stack corrupt case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string empty error
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 0, (unsigned char*)"");

	dg_forthstringtoc(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtocname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc string offset stack corrupt case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringemptyerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc string offset stack corrupt case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error popping character from string buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthstringtoc(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtocname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error popping character from string buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackstringbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error popping character from string buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferbytename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error popping character from string buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// error pushing datastack
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthstringtoc(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtocname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error pushing datastack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error pushing datastack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc error pushing datastack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");


	dg_forthstringtoc(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'s')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - wrong character returned on data stack \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2*sizeof(UINT64));

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 5) != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringcstore success case 1 - string 2 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 7) != 'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - string 2 char 2 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringtoc success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthstringto()
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

	const char* pError = NULL;
	UINT64 testint = 0;
	UINT64 t2 = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstringto\n");
#ifndef DGLU_NO_DIAPER

	// error getting pointer to string offset stack
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthstringto(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error getting pointer to string offset stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error getting pointer to string offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error getting pointer to string offset stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string stack underflow error
	dg_initbuffers(&BHarrayhead);

	dg_forthstringto(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto string stack underflow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto string stack underflow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string offset stack corrupt
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");

	testint = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);
	t2 = dg_popbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, testint);
	dg_pushbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, t2);

	dg_forthstringto(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto string offset stack corrupt case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsoffsetscorruptname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto string offset stack corrupt case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// string underflow error
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"dog");

	dg_forthstringto(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto string offset stack corrupt case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto string offset stack corrupt case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error popping UINT64 from string buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"catcats");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 8, (unsigned char*)"zetabeta");

	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthstringto(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error popping UINT64 from string buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackstringbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error popping UINT64 from string buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error popping UINT64 from string buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// error pushing UINT64 to datastack
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"catcats");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 8, (unsigned char*)"zetabeta");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthstringto(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringtoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error pushing datastack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error pushing datastack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto error pushing datastack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 7, (unsigned char*)"catcats");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"zeo");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 8, (unsigned char*)"abcdefgh");


	dg_forthstringto(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	// assumes little endian processor like 0x86
	if (testint != 0x6867666564636261)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - wrong character returned on data stack \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2*sizeof(UINT64));

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 7) != 'z')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - string 2 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 8) != 'e')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - string 2 char 2 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringto success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthctostring ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthctostring\n");
#ifndef DGLU_NO_DIAPER

	// error doing chartostring
	dg_initbuffers(&BHarrayhead);

	dg_forthctostring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthctostringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring error doing chartostring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthctonewstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring error doing chartostring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error doing dg_forthcatstring
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)'k');

	dg_forthctostring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthctostringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring error doing dg_forthcatstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcatstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring error doing dg_forthcatstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)'k');


	dg_forthctostring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2*sizeof(UINT64));

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - end of string 2 offset not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 8) != 's')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - string 2 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 9) != 'k')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - string 2 char 2 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthctostring success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthtostring()
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

	const char* pError = NULL;
	UINT64 testint = 0;
    unsigned char c;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthtostring\n");
#ifndef DGLU_NO_DIAPER

	// error doing dg_forthtonewstring
	dg_initbuffers(&BHarrayhead);

	dg_forthtostring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtostringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring error doing dg_forthtonewstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtonewstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring error doing dg_forthtonewstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error doing dg_forthcatstring
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x41424344);

	dg_forthtostring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtostringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring error doing dg_forthcatstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcatstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring error doing dg_forthcatstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 2, (unsigned char*)"ze");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 8, (unsigned char*)"dogsdigs");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x4142434445464748);


	dg_forthtostring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - end of string 0 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - end of string 1 offset not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2*sizeof(UINT64));

	if (testint != 21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - end of string 2 offset not what expected\n");
	}

    c = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 12);
    
	if (c != 's')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - string 2 char 7 not what expected, expected 's', got ");
        dg_writestdout(&BHarrayhead, (unsigned char*)&c, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    c = dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 13);
    
	if (c != 'H')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - string 3 char 0 not what expected, expected 'H', got ");
        dg_writestdout(&BHarrayhead, (unsigned char*)&c, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthtostring success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthstringquotes ()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstringquotes\n");
#ifndef DGLU_NO_DIAPER

	// error getting current input buffer
	dg_initbuffers(&BHarrayhead);

	dg_forthstringquotes(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringquotesname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes error getting current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes error getting current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting pointer to current input buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 2384);

	dg_forthstringquotes(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringquotesname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing lstring
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 11, (unsigned char*)"cat dog rat");

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthstringquotes(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringquotesname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes error pushing lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes error pushing lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success cases 1 	
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 11, (unsigned char*)"cat\" dog rat" );

	dg_forthstringquotes(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - end of string 0 offset not what expected\n");
	}


	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 0) != 'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - string 0 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 2) != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - string 0 char 2 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstringquotes success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// would be nice to test more cases
}


void testdg_forthholdstring ()
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

	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthholdstring\n");

	// success cases 1 	
	dg_initbuffers(&BHarrayhead);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)'z');

	dg_forthholdstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - error count not 0 \n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - number of strings on stack not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - string offset buffer length not what expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - string string buffer length not what expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - end of string 0 offset not what expected\n");
	}


	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 0) != 'z')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - string 0 char 0 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 1) != 'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - string 0 char 1 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 2) != 'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - string 0 char 2 not what expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 3) != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - string 0 char 3 not what expected\n");
	}
	
	testint = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! forthholdstring dg_success case 1 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// would be nice to test more cases
}


void testdg_forthnumbersignstring()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnumbersignstring\n");
#ifndef DGLU_NO_DIAPER
	// unable to get base error
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASPACE_BUFFERID); // basevariable is in dataspace buffer
	 // check error here

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	 // check error here

	dg_forthnumbersignstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring unable to get base case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring unable to get base case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring unable to get base case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
	
	// base too low case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring base too low case - unable to initialize buffers\n");
		return;
	}

	dg_initvariables(&BHarrayhead); // base is 10 after this

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring base too low case - unable to initialize variables\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring base too low case - unable to push test number to data stack\n");
		return;
	}

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 0x1);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring base too low case - unable to initialize base variable\n");
		return;
	}

	dg_forthnumbersignstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring base too low case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_basetoolowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring base too low case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// test error pushing base
	// test error doing dg_forthudmslashmod
	// can't really get error popping remainder
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); // base is 10 after this

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnewstring(&BHarrayhead);

	dg_forthnumbersignstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case ds 9 $ '' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case ds 9 $ '' - 0 not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case ds 9 $ '' - 0 not returned on data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case ds 9 $ '' - data stack not balanced after test\n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - $ length not 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 0 not 9\n");
	}

	dg_forthdepthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - number of strings on stack not 1\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	// success case 2
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 345);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnumbersignstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 2 ds 345 $ '9' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 2 ds 345 $ '9' - hi 0 not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 34)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 2 ds 345 $ '9' - lo 34 not returned on data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 2 ds 345 $ '9' - data stack not balanced after test\n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - $ length not 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 0 not 5\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 1 not 5\n");
	}

	dg_forthdepthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - number of strings on stack not 1\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	// success case 3
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 34);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnumbersignstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 3 ds 34 $ '59' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 3 ds 34 $ '59' - 0 hi not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 3 ds 34 $ '59' - 3 lo not returned on data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 3 ds 34 $ '59' - data stack not balanced after test\n");
	}


	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - $ length not 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'4')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 0 not 5\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 1 not 5\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 2 not 5\n");
	}

	dg_forthdepthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - number of strings on stack not 1\n");
	}

	dg_clearerrors(&BHarrayhead);

	// success case 4
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 16);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x3847);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x5A);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_forthnumbersignstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 4 ds 5A $ '594' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 4 ds 5A $ '594' - 0 hi not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 4 ds 5A $ '594' - 5 lo not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x3847)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignstring success case 4 ds 5A $ '594' - data stack corrupted\n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - $ length not 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'A')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 0 not 5\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'4')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 1 not 5\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 2 not 5\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - char 3 not 5\n");
	}

	dg_forthdepthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring success case ds 9 $ '' - number of strings on stack not 1\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignstring success case 4 ds 5A $ '594' - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	// error pushing lstring
	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 34);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnumbersignstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring error inserting in $ case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthholdstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersignstring error inserting in $ case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthnumbersignsstring()
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

	const char* pError = NULL;
	UINT64 testint = 0;
    unsigned char c;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnumbersignsstring\n");
#ifndef DGLU_NO_DIAPER
	// error doing dg_forthnumbersignstring
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! store error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthnumbersignsstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignsstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring error doing dg_forthnumbersignstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring error doing dg_forthnumbersignstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to data stack dont know how to get this one if dg_forthnumbersignstring worked
	// u1 missing (underflow) case dont know how to get this one if dg_forthnumbersignstring worked	
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthnewstring(&BHarrayhead);

	dg_forthnumbersignsstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignsstring success case 1 n = 0 base 10 - got wrong error\n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 1 n = 0 base 10 - expected $ length 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'0')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 1 n = 0 base 10 - expected $[0] = '0'\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 1 n = 0 base 10 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 1 n = 0 base 10 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 1 n = 0 base 10 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 32);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthnewstring(&BHarrayhead);

	dg_forthnumbersignsstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignsstring success case 2 n = 32 base 10 - got wrong error\n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 2 n = 32 base 10 - expected $ length 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'3')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 2 n = 32 base 10 - expected $[0] = '0'\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'2')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 2 n = 32 base 10 - expected $[1] = '0'\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 2 n = 32 base 10 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 2 n = 32 base 10 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 2 n = 32 base 10 - data stack not balanced after test\n");
	}


	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 3
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_forthnewstring(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 456);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthnumbersignsstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignsstring success case 3 n = 456 base 10 - got wrong error\n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected $ length 3 , got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'4')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected $[0] = '0'\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case  3 n = 456 base 10 - expected $[1] = '0'\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'6')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected $[2] = '0'\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - data stack not balanced after test\n");
	}


	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 4
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_forthnewstring(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 16);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFFFFFFFFFF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFFFFFFFFFF);

	dg_forthnumbersignsstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignsstring success case 4 n = -1 base 10 - got wrong error\n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 32)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 4 n = -1 base 10 - expected $ length 32, got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 4 n = -1 base 16 - expected $[0] = '0'\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case  4 n = -1 base 16 - expected $[1] = '0'\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 31);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'F')
	{
        c = (unsigned char)testint;
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 4 n = -1 base 16 - expected $[31] = 'F'\n ");
        dg_writestdout(&BHarrayhead, (unsigned char*)&c, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 4 n = -1 base 16 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 4 n = -1 base 16 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 4 n = -1 base 16 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 5
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 16);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xF88);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFF);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_forthnewstring(&BHarrayhead);

	dg_forthnumbersignsstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersignsstring success case 5 n = 32 base 10 - got wrong error\n");
	}


	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected $ length 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected $[0] = '0'\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case  3 n = 456 base 10 - expected $[1] = '0'\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 7);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (unsigned char)'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 3 n = 456 base 10 - expected $[7] = '0'\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 5 n = 0xFFFFFFFF base 16 - expected data stack result to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 5 n = 0xFFFFFFFF base 16 - expected return lo to be 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xF88)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 5 n = 0xFFFFFFFF base 16 - data stack corrupted\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersignsstring success case 5 n = 0xFFFFFFFF base 16 - data stack not balanced after test\n"); 
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthsignstring()
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

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthsignstring\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthsignstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsignstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// dont know how to get push '-' error if pop n worked


	// error inserting character at beginning of string
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);

	dg_forthsignstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsignstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring error inserting character at beginning of string case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthholdstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring error inserting character at beginning of string case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39);

	dg_forthnewstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case - unable to initialize data stack");
		return;
	}

	dg_forthsignstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case - got an error \n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case - expected string length to not change\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);

	// success case 2
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case 2 - unable to initialize data stack");
		return;
	}

	dg_forthsignstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case 2 - got an error \n");
	}

	dg_forthlengthstring(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case 2 - expected string length be 1\n");
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstringcfetch(&BHarrayhead);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)'-')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case 2 - expected char 0 to be '-'\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsignstring success case 2 - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthsplitstring()
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

	Bufferhandle* pBH = NULL;

	const char* pError = NULL;
	UINT64 testint = 0;

	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthsplitstring\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthsplitstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsplitstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting pointer to string offset stack
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthsplitstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsplitstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring error getting pointer to string offset stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring error getting pointer to string offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring error getting pointer to string offset stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_forthsplitstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsplitstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring string stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring string stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string stack corrupt
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_putbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0, 7);
	dg_putbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 4, 4);

	dg_forthsplitstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsplitstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring string stack corrupt case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsoffsetscorrupt)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring string stack corrupt case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// n > length
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthsplitstring(&BHarrayhead); 

	testint = ::dg_getlstringlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring n > length case - expected string length to be 0");
	}

	testint = ::dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring n > length case - expected 3 strings on string stack");
	}

    //pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_forthsplitstringname)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring n > length case - got wrong error 1 below top, got ");
    //  dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //  dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

	//pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_lstringoffsetpastenderror)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring n > length case - got wrong error 1 below top, got ");
    //  dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //  dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing endoffset case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	
	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_STRINGOFFSETSTACK_BUFFERID] );

	pBH->size    = pBH->nextunusedbyte;
	pBH->maxsize = pBH->nextunusedbyte;
	pBH->growby  = pBH->nextunusedbyte;

	dg_forthsplitstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsplitstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! error pushing endoffset case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! error pushing endoffset case case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! error pushing endoffset case case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthsplitstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - didn't get expected number of strings on stack\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - cant get pointer to string stack's string buffer\n");
		return;
	}

	if (pbuffer[0] != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - string 0 char 0 not what was expected\n");
	}

	if (pbuffer[1] != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - string 0 char 1 not what was expected\n");
	}

	if (pbuffer[2] != 'g')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - string 1 char 0 not what was expected\n");
	}

	if (pbuffer[3] != 's')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - string 1 char 1 not what was expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - string stack's offset buffer length not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - end offset of string 0 not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case - end offset of string 1 not what was expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthsplitstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 2 - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 2 - didn't get expected number of strings on stack\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 2 - string stack's offset buffer length not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 2 - end offset of string 0 not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 2 - end offset of string 1 not what was expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 3
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthsplitstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 3 - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 3 - didn't get expected number of strings on stack\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 3 - string stack's offset buffer length not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 3 - end offset of string 0 not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 3 - end offset of string 1 not what was expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 4
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthsplitstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 4 - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 4 - didn't get expected number of strings on stack\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 3*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 4 - string stack's offset buffer length not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 4 - end offset of string 0 not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 4 - end offset of string 1 not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 2*sizeof(UINT64));

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsplitstring success case 4 - end offset of string 2 not what was expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthputmidstring()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	UINT64 testint = 0;

	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthputmidstring\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting pointer to string offset stack
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error getting pointer to string offset stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackoffsetbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error getting pointer to string offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error getting pointer to string offset stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string stack corrupt 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 6, (unsigned char*)"horses");

	dg_putbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0, 7);
	dg_putbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 4, 3);

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string stack corrupt 1 case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsoffsetscorrupt)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string stack corrupt 1 case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string stack corrupt 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 6, (unsigned char*)"horses");

	dg_putbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 4, 13);
	dg_putbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 8, 7);
	
	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string stack corrupt 2 case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringsoffsetscorrupt)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string stack corrupt 2 case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// n > string 1 length
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring n > string 1 length case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringoffsetpastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring n > string 1 length case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string2 length > string 1 length - n
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string2 length > string 1 length - n case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringoffsetpastenderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string2 length > string 1 length - n case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to string buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	
	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error getting pointer to string buffer - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstringstackstringbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error getting pointer to string buffer - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring error getting pointer to string buffer - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string buffer length is wrong
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	
	dg_shrinkbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, 1, &pError);

	dg_forthputmidstring(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthputmidstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string buffer length is wrong case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_lstringtopoffsetwasbad)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring string buffer length is wrong case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthputmidstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - didn't get expected number of strings on stack\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - cant get pointer to string stack's string buffer\n");
		return;
	}

	if (pbuffer[0] != 'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - string 0 char 0 not what was expected\n");
	}

	if (pbuffer[1] != 'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - string 0 char 1 not what was expected\n");
	}

	if (pbuffer[2] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - string 0 char 2 not what was expected\n");
	}

	if (pbuffer[3] != 's')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - string 0 char 3 not what was expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - string stack's offset buffer length not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - end offset of string 0 not what was expected\n");
	}

	if (*plength != 4)
	{	
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case - stringbufferlength not what was expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 5, (unsigned char*)"doggy");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthputmidstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - didn't get expected number of strings on stack\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - cant get pointer to string stack's string buffer\n");
		return;
	}

	if (pbuffer[0] != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - string 0 char 0 not what was expected\n");
	}

	if (pbuffer[1] != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - string 0 char 1 not what was expected\n");
	}

	if (pbuffer[2] != 'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - string 0 char 2 not what was expected\n");
	}

	if (pbuffer[3] != 'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - string 0 char 3 not what was expected\n");
	}

	if (pbuffer[4] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - string 0 char 4 not what was expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - string stack's offset buffer length not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - end offset of string 0 not what was expected\n");
	}

	if (*plength != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 2 - stringbufferlength not what was expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"mice");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 5, (unsigned char*)"doggy");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthputmidstring(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - didn't get expected number of strings on stack\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - cant get pointer to string stack's string buffer\n");
		return;
	}

	if (pbuffer[4] != 'd')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - string 0 char 0 not what was expected\n");
	}

	if (pbuffer[5] != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - string 0 char 1 not what was expected\n");
	}

	if (pbuffer[6] != 'c')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - string 0 char 2 not what was expected\n");
	}

	if (pbuffer[7] != 'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - string 0 char 3 not what was expected\n");
	}

	if (pbuffer[8] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - string 0 char 4 not what was expected\n");
	}

	testint = dg_getbufferlength(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - string stack's offset buffer length not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, 0);

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - end offset of string 0 not what was expected\n");
	}

	testint = dg_getbufferuint64(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, sizeof(UINT64));

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - end offset of string 1 not what was expected\n");
	}

	if (*plength != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthputmidstring success case 3 - stringbufferlength not what was expected\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);	
}


void testdg_forthgetsstringnd()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	UINT64 testint = 0;

	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetsstringnd\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthgetsstringnd(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetsstringndname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// error getting depth of string stack
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_freebuffer(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	dg_forthgetsstringnd(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetsstringndname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd error getting pointer to string offset stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd error getting pointer to string offset stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// string stack underflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthgetsstringnd(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetsstringndname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd string stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_stringstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd string stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to string buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");
	
	dg_freebuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID);

	dg_forthgetsstringnd(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetsstringndname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd error getting pointer to string buffer - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd error getting pointer to string buffer - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 4, (unsigned char*)"dogs");
	dg_pushlstring(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID, DG_STRINGSTRINGSTACK_BUFFERID, 3, (unsigned char*)"cat");

	dg_forthgetsstringnd(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd success case - got an error \n");
	}

	testint = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd success case - didn't get expected number of strings on stack\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd success case - cant get pointer to string stack's string buffer\n");
		return;
	}

	testint = dg_popdatastack(&BHarrayhead);
    
    if (testint != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd success case - wrong string length returned, got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    testint = dg_popdatastack(&BHarrayhead);
    
    if (testint != (UINT64)(pbuffer+4))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetsstringnd success case - wrong pointer returned\n");
    }
    
	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthwordsstringquotes()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;
    UINT64 stringlength;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthwordsstringquotes\n");

    
    // success case empty strings stack
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead); // need this to make room in dataspace buffer I think

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error setting currentinterpretbuffer \n");
        return;
    }

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)"once apon a time \" there was anime\x00");  // comes with 0 at end...
                                                                 // first character is skipped
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error filling terminal input buffer\n");
        return;
    }

    dg_forthwordsstringquotes(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error \n");
    }

    testint = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error getting number of lstrings on string stack\n");
        return;
    }

    if (testint != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - didn't get expected number of strings on stack\n");
    }
    
    pbuffer = dg_getpbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, &plength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error getting pointer to string stack string buffer\n");
        return;
    }

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - cant get pointer to string stack's string buffer\n");
        return;
    }

    testint = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error popping the data stack\n");
        return;
    }
    
    if (testint != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - wrong number of strings pushed returned expected 4 , got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ((pbuffer[0] != 'o') ||
        (pbuffer[4] != 'a') ||
        (pbuffer[8] != 'a') ||
        (pbuffer[9] != 't') ||
        (pbuffer[12] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - wrong string data in string buffer. Expected 'onceaponatime', got '");
        dg_writestdoutraw(&BHarrayhead, pbuffer, *plength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pbuffer = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error getting a pointer to first lstring on the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
        
    if (stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - first string pushed has wrong length. Expected 4 , got ");
        dg_writestdoutuinttodec(&BHarrayhead, *plength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ((pbuffer[0] != 'o') ||
        (pbuffer[1] != 'n') ||
        (pbuffer[2] != 'c') ||
        (pbuffer[3] != 'e'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - wrong string data in first string. Expected 'once', got '");
        dg_writestdoutraw(&BHarrayhead, pbuffer, *plength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pbuffer = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - got an error getting a pointer to second lstring on the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
    
    if (stringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - second string pushed has wrong length. Expected 4 , got ");
        dg_writestdoutuinttodec(&BHarrayhead, *plength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ((pbuffer[0] != 'a') ||
        (pbuffer[1] != 'p') ||
        (pbuffer[2] != 'o') ||
        (pbuffer[3] != 'n'))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordsstringquotes success case - wrong string data in second string. Expected 'apon', got '");
        dg_writestdoutraw(&BHarrayhead, pbuffer, *plength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthwords0stringquotes()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    UINT64 testint = 0;

    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;
    UINT64 stringlength;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthwords0stringquotes\n");

    
    // success case empty strings stack
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead); // need this to make room in dataspace buffer I think

    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        DG_TERMINALINPUT_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error setting currentinterpretbuffer \n");
        return;
    }

    dg_push0stringtobuffersegment(
        &BHarrayhead,
        DG_TERMINALINPUT_BUFFERID,
        (unsigned char*)"once apon a time \" there was anime\x00");  // comes with 0 at end...
                                                                 // first character is skipped
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error filling terminal input buffer\n");
        return;
    }

    dg_forthwords0stringquotes(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error \n");
    }

    testint = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error getting number of lstrings on string stack\n");
        return;
    }

    if (testint != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - didn't get expected number of strings on stack\n");
    }
    
    pbuffer = dg_getpbuffer(&BHarrayhead, DG_STRINGSTRINGSTACK_BUFFERID, &plength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error getting pointer to string stack string buffer\n");
        return;
    }

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - cant get pointer to string stack's string buffer\n");
        return;
    }

    testint = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error popping the data stack\n");
        return;
    }
    
    if (testint != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - wrong number of strings pushed returned expected 4 , got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ((pbuffer[0] != 'o') ||
        (pbuffer[1] != 'n') ||
        (pbuffer[2] != 'c') ||
        (pbuffer[3] != 'e') ||
        (pbuffer[4] != 0) ||
        (pbuffer[5] != 'a') ||
        (pbuffer[6] != 'p') ||
        (pbuffer[7] != 'o') ||
        (pbuffer[8] != 'n') ||
        (pbuffer[9] != 0) ||
        (pbuffer[10] != 'a') ||
        (pbuffer[11] != 0) ||
        (pbuffer[12] != 't') ||
        (pbuffer[15] != 'e') ||
        (pbuffer[16] != 0))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - wrong string data in string buffer. Expected 'once.apon.a.time.', got '");
        dg_writestdoutraw(&BHarrayhead, pbuffer, *plength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pbuffer = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error getting a pointer to first lstring on the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
        
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - first string pushed has wrong length. Expected 4 , got ");
        dg_writestdoutuinttodec(&BHarrayhead, *plength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ((pbuffer[0] != 'o') ||
        (pbuffer[1] != 'n') ||
        (pbuffer[2] != 'c') ||
        (pbuffer[3] != 'e') ||
        (pbuffer[4] != 0))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - wrong string data in first string. Expected 'once', got '");
        dg_writestdoutraw(&BHarrayhead, pbuffer, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    pbuffer = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &stringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - got an error getting a pointer to second lstring on the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
    
    if (stringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - second string pushed has wrong length. Expected 4 , got ");
        dg_writestdoutuinttodec(&BHarrayhead, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ((pbuffer[0] != 'a') ||
        (pbuffer[1] != 'p') ||
        (pbuffer[2] != 'o') ||
        (pbuffer[3] != 'n') ||
        (pbuffer[4] != 0))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwords0stringquotes success case - wrong string data in second string. Expected 'apon', got '");
        dg_writestdoutraw(&BHarrayhead, pbuffer, stringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
        return;
    }
    
    
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthgetargsfromnstrings()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetargsfromnstrings\n");

    
    // success case empty
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"puppy");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushdatastack(
        &BHarrayhead,
        2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error pushing 2 to data stack\n");
        return;
    }

    dg_forthgetargsfromnstrings(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error doing dg_forthgetargsfromnstrings\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (((UINT64*)(pstring2))[0] != (UINT64)pstring0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - pointer in string 4 to 2nd string is incorrect.\n");
        return;
    }
    
    if (((UINT64*)(pstring2))[1] != (UINT64)pstring1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - pointer in string 4 to third string is incorrect.\n");
        return;
    }
    
    if (((UINT64*)(pstring2))[2] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - pointer in string 4 to end string is not NULL.\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - got an error popping pointer off data stack\n");
        return;
    }
        
    if (x != (UINT64)pstring2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetargsfromnstrings success case - pointer returned has wrong value. Got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthnotstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnotstring\n");

    
    // success case empty
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x32\x43\x54\x65");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - got an error pushing third string\n");
        return;
    }

    dg_forthnotstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - got an error doing dg_forthnotstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x21\x32\43\x54\x65
    if (pstring2[0] != 0xde)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0xcd)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0xbc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - byte 2 of second string is incorrect. Expected 0xbc, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xab)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x9a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnotstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthreversestring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthreversestring\n");

    
    // success case empty
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x32\x43\x54\x65");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - got an error pushing third string\n");
        return;
    }

    dg_forthreversestring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - got an error doing dg_forthnotstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x21\x32\43\x54\x65
    if (pstring2[0] != 0x65)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x54)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x43)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x21)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthreversestring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthlelshiftstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlelshiftstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x32\x43\x54\x65");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error pushing third string\n");
        return;
    }
    
    /*
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error pushing carry to data stack\n");
        return;
    }
    */

    dg_forthlelshiftstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error doing dg_forthlelshiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error popping the data stack\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x20\x32\43\x54\x65
    if (pstring2[0] != 0x42)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xa8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xca)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // success case carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x32\x43\x54\xe5");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error pushing third string\n");
        return;
    }
    
    /*
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error pushing carry to data stack\n");
        return;
    }
    */

    dg_forthlelshiftstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error doing dg_forthlelshiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error popping the data stack\n");
        return;
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x21\x32\43\x54\x65
    if (pstring2[0] != 0x42)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xa8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xca)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case carry - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthulershiftstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulershiftstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error pushing third string\n");
        return;
    }
    
    /*
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error pushing carry to data stack\n");
        return;
    }
    */

    dg_forthulershiftstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error doing dg_forthulershiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error popping the data stack\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x20\x33\x42\x54\xe4
    if (pstring2[0] != 0x90)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x21)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x2a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x72)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // success case carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x33\x42\x54\x64");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error pushing third string\n");
        return;
    }
    
    /*
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftstring success case - got an error pushing carry to data stack\n");
        return;
    }
    */

    dg_forthulershiftstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error doing dg_forthulershiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error popping the data stack\n");
        return;
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x21\x32\43\x54\x65
    if (pstring2[0] != 0x90)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x21)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x2a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulershiftstring success case carry - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthslershiftstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthslershiftstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error pushing third string\n");
        return;
    }
    
    /*
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error pushing carry to data stack\n");
        return;
    }
    */

    dg_forthslershiftstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error doing dg_forthslershiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error popping the data stack\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x20\x33\x42\x54\xe4
    if (pstring2[0] != 0x90)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x21)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x2a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xf2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // success case carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x33\x42\x54\x64");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error pushing third string\n");
        return;
    }
    
    /*
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case - got an error pushing carry to data stack\n");
        return;
    }
    */

    dg_forthslershiftstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error doing dg_forthslershiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error popping the data stack\n");
        return;
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x21\x32\43\x54\x65
    if (pstring2[0] != 0x90)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x21)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x2a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthslershiftstring success case carry - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthlelshiftcstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlelshiftcstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x32\x43\x54\x65");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error pushing third string\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error pushing carry to data stack\n");
        return;
    }

    dg_forthlelshiftcstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error doing dg_forthlelshiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error popping the data stack\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x20\x32\43\x54\x65
    if (pstring2[0] != 0x42)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xa8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xca)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // success case carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x32\x43\x54\xe5");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error pushing third string\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case - got an error pushing carry to data stack\n");
        return;
    }

    dg_forthlelshiftcstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error doing dg_forthlelshiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error popping the data stack\n");
        return;
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x21\x32\43\x54\x65
    if (pstring2[0] != 0x43)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x86)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xa8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xca)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlelshiftcstring success case carry - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthlershiftcstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlershiftcstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error pushing carry to data stack\n");
        return;
    }


    dg_forthlershiftcstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error doing dg_forthlershiftcstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error popping the data stack\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x20\x33\x42\x54\xe4
    if (pstring2[0] != 0x90)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x21)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x2a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x72)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // success case carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x21\x33\x42\x54\x64");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error pushing third string\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case - got an error pushing carry to data stack\n");
        return;
    }

    dg_forthlershiftcstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error doing dg_forthulershiftstring\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error popping the data stack\n");
        return;
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got wrong carry out\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x21\x32\43\x54\x65
    if (pstring2[0] != 0x90)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x21)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - byte 2 of second string is incorrect. Expected 0x43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x2a)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xb2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlershiftcstring success case carry - byte 4 of second string is incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthuleandstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthuleandstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"\xFF\x0F\xF0");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error pushing third string\n");
        return;
    }

    dg_forthuleandstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error doing dg_forthlershiftcstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x20\x03\x40\x00\x00
    if (pstring2[0] != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x03)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x40)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - byte 2 of second string is incorrect. Expected 0x40, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - got an error getting depth of string stack\n");
        return;
    }
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleandstring success case - depth of string stack incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthuleorstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthuleorstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"\xFF\x0F\xF0");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error pushing third string\n");
        return;
    }

    dg_forthuleorstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error doing dg_forthuleorstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \xff\x3f\xf2\x54\xe4
    if (pstring2[0] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x3f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0xf2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - byte 2 of second string is incorrect. Expected 0x40, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x54)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xe4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - got an error getting depth of string stack\n");
        return;
    }
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthuleorstring success case - depth of string stack incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthulexorstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulexorstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"\xFF\x0F\xF0");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error pushing third string\n");
        return;
    }

    dg_forthulexorstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error doing dg_forthulexorstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \xdf\x3c\xb2\x54\xe4
    if (pstring2[0] != 0xdf)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0x3c)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0xb2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - byte 2 of second string is incorrect. Expected 0x40, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0x54)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xe4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - got an error getting depth of string stack\n");
        return;
    }
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexorstring success case - depth of string stack incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthulenandstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulenandstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"\xFF\x0F\xF0");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error pushing third string\n");
        return;
    }

    dg_forthulenandstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error doing dg_forthulenandstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \x20\x03\x40\x00\x00
    if (pstring2[0] != 0xdf)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0xfc)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0xbf)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - byte 2 of second string is incorrect. Expected 0x40, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0xff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - got an error getting depth of string stack\n");
        return;
    }
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenandstring success case - depth of string stack incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthulenorstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulenorstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"\xFF\x0F\xF0");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error pushing third string\n");
        return;
    }

    dg_forthulenorstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error doing dg_forthulenorstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \xff\x3f\xf2\x54\xe4
    if (pstring2[0] != 0x00)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0xC0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x0d)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - byte 2 of second string is incorrect. Expected 0x40, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xab)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x1b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - got an error getting depth of string stack\n");
        return;
    }
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulenorstring success case - depth of string stack incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthulexnorstring()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError = NULL;
    
    unsigned char* pstring0;
    UINT64 string0length;
    
    unsigned char* pstring1;
    UINT64 string1length;
    
    unsigned char* pstring2;
    UINT64 string2length;
    
    UINT64 x;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthulexnorstring\n");

    
    // success case no carry
    dg_initbuffers(&BHarrayhead);

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"cat");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error pushing first string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        4,
        (unsigned char*)"wolf");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error pushing second string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        5,
        (unsigned char*)"\x20\x33\x42\x54\xe4");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error pushing third string\n");
        return;
    }
    
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        3,
        (unsigned char*)"\xFF\x0F\xF0");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error pushing third string\n");
        return;
    }

    dg_forthulexnorstring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error doing dg_forthulexnorstring\n");
        return;
    }
    
    pstring0 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &string0length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error getting pointer to second string\n");
        return;
    }
    
    pstring1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        &string1length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error getting pointer to third string\n");
        return;
    }
    
    pstring2 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        &string2length);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error getting pointer to fourth string\n");
        return;
    }
    
    if (pstring0[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - byte 0 of zero string is incorrect.\n");
        return;
    }
    
    if (pstring1[0] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - byte 0 of 1st string is incorrect.\n");
        return;
    }
    
    // \xdf\x3c\xb2\x54\xe4
    if (pstring2[0] != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - byte 0 of 2nd string is incorrect.\n");
        return;
    }
    
    if (pstring2[1] != 0xc3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - byte 1 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[2] != 0x4d)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - byte 2 of second string is incorrect. Expected 0x40, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)pstring2[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    if (pstring2[3] != 0xab)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - byte 3 of second string is incorrect.\n");
        return;
    }
    
    if (pstring2[4] != 0x1b)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - byte 4 of second string is incorrect.\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - got an error getting depth of string stack\n");
        return;
    }
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthulexnorstring success case - depth of string stack incorrect.\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


/*
void testdg_forthfreelibrary()
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
//	UINT64 testint = 0;

//	UINT64 bufid = 0;
//	UINT64* plength = NULL;
//	unsigned char* pbuffer = NULL;

//	unsigned char* ppad = NULL;
//	UINT64* ppadlength = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthfreelibrary - need test\n");
}
*/
