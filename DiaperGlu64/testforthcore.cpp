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
#include "testdglu.h"

void testdg_forthstore()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing !\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthstore(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore error getting pointer to data stack case - got wrong error");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// address and maybe data missing case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x5566778899aabbcc);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore address and maybe data missing case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthstore(&BHarrayhead);

	if (dg_poperror(&BHarrayhead) != dg_forthstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore address and maybe data missing case - got wrong error for name");
	}

    if (dg_poperror(&BHarrayhead) != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore address and maybe data missing case - got wrong error");
	}


	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// illegal address error

	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x123456789abcdef0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFFFFFFFFFF); // hopefully this is an illegal address

	dg_forthstore(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore illegal address case - got wrong error for name\n");
	}

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_badmemoryerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore illegal address case - got wrong error \n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// dg_success case
	dg_initbuffers(&BHarrayhead);

	testint = 0;

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x4567890116258374);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);

	dg_forthstore(&BHarrayhead);

	if (testint != 0x4567890116258374)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore dg_success case - number wasn't dg_forthstored");
	}

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore dg_success case - error count not 0");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore dg_success case - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// dg_success case 2
	dg_initbuffers(&BHarrayhead);

	testint = 0;

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x33445566778899aa);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x4567890116258372);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);

	dg_forthstore(&BHarrayhead);

	if (testint != 0x4567890116258372)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore dg_success case - number wasn't dg_forthstored");
	}

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore dg_success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x33445566778899aa)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore dg_success case - data stack corrupted");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore dg_success case - data stack not balanced after test \n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    		
}


void testdg_forthnumbersign()
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

	unsigned char* ppad = NULL;
	UINT64* ppadlength = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing #\n");

	// unable to get base error
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASPACE_BUFFERID); // basevariable is in dataspace buffer
	 // check error here

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	 // check error here

	dg_forthnumbersign(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign unable to get base case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign unable to get base case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
	
	// base too low case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign base too low case - unable to initialize buffers\n");
		return;
	}

	dg_initvariables(&BHarrayhead); // base is 10 after this

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign base too low case - unable to initialize variables\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign base too low case - unable to push test number to data stack\n");
		return;
	}

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 0x1);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign base too low case - unable to initialize base variable\n");
		return;
	}

	dg_forthnumbersign(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign base too low case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_basetoolowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign base too low case - got wrong error 1 below top\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// test error pushing base
	// test error doing dg_forthudmslashmod
	// can't really get error popping remainder

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); // base is 10 after this

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnumbersign(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case ds 9 pad '' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case ds 9 pad '' - 0 not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case ds 9 pad '' - 0 not returned on data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case ds 9 pad '' - data stack not balanced after test\n");
	}

	ppad = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &ppadlength);

	if (ppad == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign success case ds 9 pad '' - unable to get pointer to pad buffer\n");
		return;
	}

	if (*ppadlength != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case ds 9 pad '' - pad length not 1\n");
	}

	if (ppad[0] != '9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case ds 9 pad '' - 9 not at first character of pad\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	// success case 2
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 345);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnumbersign(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 2 ds 345 pad '9' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 2 ds 345 pad '9' - hi 0 not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 34)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 2 ds 345 pad '9' - lo 34 not returned on data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 2 ds 345 pad '9' - data stack not balanced after test\n");
	}

	ppad = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &ppadlength);

	if (ppad == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign success case 2 ds 345 pad '9' - unable to get pointer to pad buffer\n");
		return;
	}

	if (*ppadlength != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 2 ds 345 pad '9' - pad length not 2\n");
	}

	if (ppad[0] != '5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 2 ds 345 pad '9' - 5 not at first character of pad\n");
	}

	if (ppad[1] != '9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 2 ds 345 pad '9' - 9 not at second character of pad\n");
	}
	
	dg_clearerrors(&BHarrayhead);

	// success case 3
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 34);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnumbersign(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 3 ds 34 pad '59' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 3 ds 34 pad '59' - 0 hi not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 3 ds 34 pad '59' - 3 lo not returned on data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 3 ds 34 pad '59' - data stack not balanced after test\n");
	}

	ppad = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &ppadlength);

	if (ppad == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign success case 3 ds 34 pad '59' - unable to get pointer to pad buffer\n");
		return;
	}

	if (*ppadlength != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 3 ds 34 pad '59' - pad length not 3\n");
	}

	if (ppad[0] != '4')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 3 ds 34 pad '59' - 4 not at first character of pad\n");
	}

	if (ppad[1] != '5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 3 ds 34 pad '59' - 5 not at second character of pad\n");
	}

	if (ppad[2] != '9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 3 ds 34 pad '59' - 9 not at second character of pad\n");
	}

	dg_clearerrors(&BHarrayhead);

	// success case 4
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 16);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x3847);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x5A);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_forthnumbersign(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 4 ds 5A pad '594' - got an error \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 4 ds 5A pad '594' - 0 hi not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 4 ds 5A pad '594' - 5 lo not returned on data stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x3847)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersign success case 4 ds 5A pad '594' - data stack corrupted\n");
	}

	ppad = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &ppadlength);

	if (ppad == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign success case 4 ds 5A pad '594' - unable to get pointer to pad buffer\n");
		return;
	}

	if (*ppadlength != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 4 ds 5A pad '594' - pad length not 3\n");
	}

	if (ppad[0] != 'A')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 4 ds 5A pad '594' - 4 not at first character of pad\n");
	}

	if (ppad[1] != '4')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 4 ds 5A pad '594' - 4 not at first character of pad\n");
	}

	if (ppad[2] != '5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 4 ds 5A pad '594' - 5 not at second character of pad\n");
	}

	if (ppad[3] != '9')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign success case 4 ds 5A pad '594' - 9 not at second character of pad\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign success case 4 ds 5A pad '594' - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	// error inserting in pad
	dg_freebuffer(&BHarrayhead, DG_HOLD_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 34);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_forthnumbersign(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign error inserting in pad case - got wrong error \n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertinbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnumbersign error inserting in pad case - got wrong error \n");
	}
	
	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthnumbersigngreater()
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
	unsigned char* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing #>\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to data stack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthnumbersigngreater(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersigngreatername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater error getting pointer to data stack case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater error getting pointer to data stack case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// ud1 missing (underflow) case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthnumbersigngreater(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersigngreatername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigngreater data stack underflow case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigngreater data stack underflow case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// unable to get ppad error
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_HOLD_BUFFERID); 

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_forthnumbersigngreater(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersigngreatername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigngreater unable to get ppad case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigngreater unable to get ppad case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_pushbufferuint64(&BHarrayhead, DG_HOLD_BUFFERID, 0x3031323334353637);

	dg_forthnumbersigngreater(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigngreater success case - got an error\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater success case - pad length not what was expected\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (testint != (UINT64)pbuffer)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater success case - pad address missing from data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater success case - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x5566778899aabbcc);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_pushbufferuint64(&BHarrayhead, DG_HOLD_BUFFERID, 0x3031323334353637);

	dg_forthnumbersigngreater(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigngreater success case 2 - got an error\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater success case 2 - pad length not what was expected\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (testint != (UINT64)pbuffer)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater success case 2 - pad address missing from data stack\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x5566778899aabbcc)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater success case 2 - data stack corrupted\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigngreater success case 2 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);	
}


void testdg_forthnumbersigns()
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
	unsigned char* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing #S\n");
#ifndef DGLU_NO_DIAPER
	// error doing dg_forthnumbersign
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthnumbersigns(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign error doing dg_forthnumbersign case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnumbersignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersign error doing dg_forthnumbersign case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to data stack, don't know how to get this if dg_forthnumbersign worked
	// u1 missing (underflow) case don't know how to get this if dg_forthnumbersign worked
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthnumbersigns(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigns success case 1 n = 0 base 10 - got wrong error\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (*plength != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 1 n = 0 base 10 - expected pad length 1\n");
	}

	if (pbuffer[0] != '0')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 1 n = 0 base 10 - expected pad[0] = '0'\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 1 n = 0 base 10 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 1 n = 0 base 10 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 1 n = 0 base 10 - data stack not balanced after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 32);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthnumbersigns(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigns success case 2 n = 32 base 10 - got wrong error\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (*plength != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 2 n = 32 base 10 - expected pad length 2\n");
	}

	if (pbuffer[0] != '3')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 2 n = 32 base 10 - expected pad[0] = '3'\n");
	}

	if (pbuffer[1] != '2')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 2 n = 32 base 10 - expected pad[1] = '2'\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 2 n = 32 base 10 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 2 n = 32 base 10 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 2 n = 32 base 10 - data stack not balanced after test\n");
	}


	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 3
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 456);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthnumbersigns(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigns success case 3 n = 456 base 10 - got wrong error\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (*plength != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 3 n = 456 base 10 - expected pad length 3\n");
	}

	if (pbuffer[0] != '4')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 3 n = 456 base 10 - expected pad[0] = '4'\n");
	}

	if (pbuffer[1] != '5')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 3 n = 456 base 10 - expected pad[1] = '5'\n");
	}

	if (pbuffer[2] != '6')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 3 n = 456 base 10 - expected pad[2] = '6'\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 3 n = 456 base 10 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 3 n = 456 base 10 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 3 n = 456 base 10 - data stack not balanced after test\n");
	}


	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 4
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 16);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFFFFFFFFFF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFFFFFFFFFF);

	dg_forthnumbersigns(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigns success case 2 n = 32 base 10 - got wrong error\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (*plength != 32)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 4 n = 0xFFFFFFFF base 16 - expected pad length 8\n");
	}

	if (pbuffer[0] != 'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 4 n = 0xFFFFFFFF base 16 - expected pad[0] = 'F'\n");
	}

	if (pbuffer[1] != 'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 4 n = 0xFFFFFFFF base 16 - expected pad[1] = 'F'\n");
	}

	if (pbuffer[31] != 'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 4 n = 0xFFFFFFFF base 16 - expected pad[15] = 'F'\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 4 n = 0xFFFFFFFF base 16 - expected return hi to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 4 n = 0xFFFFFFFF base 16 - expected return lo to be 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 4 n = 0xFFFFFFFF base 16 - data stack not balanced after test\n");
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

	dg_forthnumbersigns(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!  dg_forthnumbersigns success case 5 n = 32 base 10 - got wrong error\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (*plength != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - expected pad length 8 \n");
	}

	if (pbuffer[0] != 'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - expected pad[0] = 'F'\n");
	}

	if (pbuffer[1] != 'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - expected pad[1] = 'F'\n");
	}

	if (pbuffer[7] != 'F')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - expected pad[2] = 'F'\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - expected data stack result to be 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - expected return lo to be 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xF88)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - data stack corrupted\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthnumbersigns success case 5 n = 0xFFFFFFFF base 16 - data stack not balanced after test\n"); 
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthtick()
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

	UINT64 cibufid = 0;

	UINT64 wordlist = 0;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing '\n");
#ifndef DGLU_NO_DIAPER
	// error getting current interpret buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthtick(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error getting current interpret buffer case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error getting current interpret buffer case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pcib
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer,9348);

	dg_forthtick(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error getting pointer to current input buffer case - got wrong error on top\n");
	}
    
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error getting pointer to current input buffer case - got wrong error 1 below top\n");
	}
#endif
	// name length = 0 error 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthtick(&BHarrayhead); // current interpret buffer is empty so namelength will be 0

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' no name error case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_wordlength0error)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' no name error case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error finding definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, 398);

	dg_forthtick(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error finding definintion case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_finddefinsearchordername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error finding definintion case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// push definition error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
 
    dg_inithlists(&BHarrayhead);   
    
    // wordlist = dg_newwordlist(&BHarrayhead, 0);

    // dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthtick(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error pushing definition case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' error pushing definition case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case - definition not found
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	dg_forthleftbracket(&BHarrayhead);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dg_forthtick(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' success case - DG_ENDOFWORDLIST missing\n");
	}

	if (length + 9 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ' success case - current input offset pointer not after delimiter after first word\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// could test dg_success case with a real definition but it should work because dg_finddefinsearchorder is tested
}


void testdg_forthparen()
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
	UINT64 cibufid = 0;
	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing (\n");
#ifndef DGLU_NO_DIAPER
	// error getting current interpret buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthparen(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthparenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( error getting current interpret buffer case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsemultilinename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( error getting current interpret buffer case - got wrong error 1 below top\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pcib
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer,9348);

	dg_forthparen(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthparenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( error getting pointer to current input buffer case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsemultilinename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( error getting pointer to current input buffer case - got wrong error on top\n");
	}
#endif
	// no more input case - should be ok 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

        // dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_PAD_BUFFERID);

	dg_forthparen(&BHarrayhead); // current interpret buffer is empty 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( no more input case - got an error\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	// dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);
        dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_PAD_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 22, (unsigned char*)"testname after ) hello");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dg_forthparen(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( success case - got an error\n");
	}

	if (length + 16 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ( success case - got an error\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthstar()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing *\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthstar(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!* (dg_forthstar) underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthstar(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) address and maybe data missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) address and maybe data missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 100 * 22
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);

	dg_forthstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 22 * 100 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 2200)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 22 * 100 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 22 * 100 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -2 * -5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);

	dg_forthstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) -2 * -5 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) -2 * -5 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) -2 * -5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 3 * -7
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);

	dg_forthstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 3 * -7 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 3 * -7 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 3 * -7 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 3 * -7 b
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);

	dg_forthstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 3 * -7 b success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 3 * -7 b success case - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 55)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 3 * -7 b success case - data stack corrupted\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! * (dg_forthstar) 3 * -7 b success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    	
}


void testdg_forthplus()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing +\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthplus(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthplus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 + 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) 65536 + 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65556)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) 65536 + 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) 65536 + 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 + 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) -1 + 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) -1 + 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! + (dg_forthplus) -1 + 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthplusstore()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing +!\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! +! error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthplusstore(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// address and maybe data missing case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore address and maybe data missing case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthplusstore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore address and maybe data missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore address and maybe data missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// illegal address error
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x12345678);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFF); // hopefully this is an illegal address

	dg_forthplusstore(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore bad address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_badmemoryerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore bad address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
#endif
    // address and maybe data missing case
    dg_initbuffers(&BHarrayhead);   

	// success case
	testint = 5;

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x45678901);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);

	dg_forthplusstore(&BHarrayhead);

	if (testint != 0x45678906)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore success case - number wasn't dg_forthplusstored");
	}

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore success case - error count not 0");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case b
	dg_initbuffers(&BHarrayhead);

	testint = 5;

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x45678901);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint);

	dg_forthplusstore(&BHarrayhead);

	if (testint != 0x45678906)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore success case b - number wasn't dg_forthplusstored\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 55)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore success case b - data stack corrupted\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore success case b - data stack not balanced after test\n");
	}

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthplusstore success case b - error count not 0\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    	
}


void testdg_checkplusloopdone ()
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

	UINT64 flag = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_checkplusloopdone\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to rstack case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_RSTACK_BUFFERID);

	flag = dg_checkplusloopdone(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_checkplusloopdonename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone error getting pointer to rstack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone error getting pointer to rstack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone error getting pointer to rstack case - expected FORTH_TRUE\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x55667788);

	flag = dg_checkplusloopdone(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_checkplusloopdonename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_rstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone parameters missing case - expected FORTH_TRUE\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error popping data stack
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 8);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	flag = dg_checkplusloopdone(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_checkplusloopdonename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone parameters missing case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone parameters missing case - expected FORTH_TRUE\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case not done
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 8);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	flag = dg_checkplusloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done - error count not 0");
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done - rstack not empty after calculation\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done - datastack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case done
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 9);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	flag = dg_checkplusloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done - error count not 0");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done - rstack not empty after calculation\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done - datastack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case not done2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	flag = dg_checkplusloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done2 - error count not 0");
	}

	if (flag != FORTH_FALSE) // this is what the standard says happens
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done2 - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done2 - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done2 - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done2 - rstack not empty after calculation\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done2 - datastack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case not done3
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 7);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	flag = dg_checkplusloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done3 - error count not 0");
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done3 - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done3 - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done3 - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done3 - rstack not empty after calculation\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case not done3 - datastack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case done2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 8);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	flag = dg_checkplusloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done2 - error count not 0");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done2 - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done2 - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done2 - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done2 - rstack not empty after calculation\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done2 - datastack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case done3
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 9);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	flag = dg_checkplusloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done3 - error count not 0");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done3 - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done3 - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done3 - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done3 - rstack not empty after calculation\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkplusloopdone success case done3 - datastack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

void testdg_forthplusloop()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	UINT64 x = 0;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing +LOOP (dg_forthplusloop)\n");
	
	
	// error getting pointer to leave buffer case
    /*
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_LEAVESTACK_BUFFERID);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthplusloop(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusloopname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP error getting pointer to leave buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthleavebufferidname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP error getting pointer to leave buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP error getting pointer to leave buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
*/
/*
	// error resolving leave case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_pushbufferuint64(&BHarrayhead, DG_LEAVESTACK_BUFFERID, 23894);

	dg_forthplusloop(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusloopname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! +LOOP error resolving leave case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! +LOOP error resolving leave case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
*/
	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	mycurrentcompilebuffer = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compile function to do DO 1+ 1 +LOOP
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not compile init locals\n");
		return;
	}
	
	dg_forthdo(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not do dg_forthdo\n");
		return;
	}
	
	dg_compilecallcore(
        &BHarrayhead,
        (UINT64)&dg_forthoneplus);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not compile call to dg_forthoneplus\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not push loop increment to data stack\n");
		return;
	}
	
	dg_forthliteral(&BHarrayhead); 
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not do dg_forthliteral\n");
		return;
	}
	
	dg_forthplusloop(&BHarrayhead); 
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case - error count not 0 got:\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"    ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"    ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"    ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        pbuffer = dg_getpbuffer(
            &BHarrayhead,
            mycurrentcompilebuffer,
            &pbufferlength);
        
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"  current compile buffer = ");
        dg_writestdoutuint64tohex(&BHarrayhead , mycurrentcompilebuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"  p current compile buffer = ");
        dg_writestdoutuint64tohex(&BHarrayhead , (UINT64)pbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"  current compile buffer length = ");
        dg_writestdoutuint64tohex(&BHarrayhead , *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_hexdumpsegment (
            &BHarrayhead,
            pbuffer,
            *pbufferlength);
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_LEAVESTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case - data  stack not empty after calculation\n");
	}		
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 16);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could push test counter to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not push loop terminator value to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - could not loop start value to data stack\n");
		return;
	}
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - got error executing compiled test routine\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 26)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case - test counter output from compiled function wrong value, probably due to incorrect loop operation, expected 26, got ");
		dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case2 
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not get current compile buffer's length\n");
		return;
	}
	
	// compile function to do DO 1+ 5 +LOOP
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not compile init locals\n");
		return;
	}
	
	dg_forthdo(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not do dg_forthdo\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)&dg_forthoneplus);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not compile call to dg_forthoneplus\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not push loop increment to data stack\n");
		return;
	}
	
	dg_forthliteral(&BHarrayhead); // compiles push number to data stack - 19 bytes
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not do dg_forthliteral\n");
		return;
	}
	
	dg_forthplusloop(&BHarrayhead); // 25 + 14 bytes 
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case2 - error count not 0");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case2 - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_LEAVESTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case2 - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case2 - data  stack not empty after calculation\n");
	}		
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 16);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not push test counter to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not push loop terminator value to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - could not push loop start value to data stack\n");
		return;
	}
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - got error calling compiled function\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 18)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case2 - test counter incorrect after calling compiled function\n");
		return;
	}
    
	dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
	
	// success case3 doing a leave 
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not get current compile buffer's length\n");
		return;
	}
	
	// compile function to do DO 1+ DUP 5 = IF LEAVE THEN 1 +LOOP
	//  depends on other functions working so +LOOP test should go at end
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not compile init locals\n");
		return;
	}
	
	dg_forthdo(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not do dg_forthdo\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthoneplus));
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not do compile call to dg_forthoneplus\n");
		return;
	}
	
	dg_forthleave(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not do dg_forthleave\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not push loop increment to data stack\n");
		return;
	}
	
	dg_forthliteral(&BHarrayhead); 
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not do dg_forthliteral\n");
		return;
	}
	
	dg_forthplusloop(&BHarrayhead);  
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case3 doing a leave - error count not 0");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case3 doing a leave - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_LEAVESTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case3 doing a leave - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! +LOOP success case3 doing a leave - data  stack not empty after calculation\n");
	}		
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 16);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not push test counter to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not push loop terminator value to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - could not push loop start value to data stack\n");
		return;
	}
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - got error calling compiled function\n");
		return;
	}
	
	// should have just done 1 loop
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 17)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing +LOOP success case3 doing a leave - test counter incorrect after calling compiled function\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
	
	// need to test more leave cases
}

void testdg_forthcomma()
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

	UINT64 bufid = 0;
	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ,\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthcomma(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , parameters missing case - unable to initialize data stack");
		return;
	}

	dg_forthcomma(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error getting current data space buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , getting current data space  buffer id case - unable to initialize data stack");
		return;
	}

	dg_forthcomma(&BHarrayhead); // variables not initialized

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error getting current data space  buffer id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error getting current data space  buffer id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error getting current data space  buffer id case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error pushing to current variable buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, 3908); // bufferid of nonexistant buffer

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , pushing to current variable buffer case - unable to initialize data stack");
		return;
	}

	dg_forthcomma(&BHarrayhead); // variables not initialized

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error pushing to current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , error pushing to current variable buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); // hopefully currentvariablebuffer is initialized

	bufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);

	length = dg_getbufferlength(&BHarrayhead, bufid);

	dg_forthcomma(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , 65536 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, bufid);

	if (testint != 65536)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , 65536 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, bufid) != length)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! , 65536 success case - current variable buffer length not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthminus()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing -\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthminus(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthminusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) error getting pointer to data stack case - got wrong error 3 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthminus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthminusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) parameters missing case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 - 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthminus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) 65536 - 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65516)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) 65536 - 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) 65536 - 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 - 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthminus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) -1 - 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) -1 - 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! - (dg_forthminus) -1 - 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}




void testdg_forthdo ()
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

	UINT64 length = 0;
	UINT64 length2;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing DO\n");

#ifndef DGLU_NO_DIAPER
	// error getting current compile buffer
	dg_initbuffers(&BHarrayhead);

	dg_forthdo(&BHarrayhead);  // variables not initialized

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdoname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO error getting current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_compilecallcorename)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO error getting current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    /*
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcompilebuffername)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO error getting current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO error getting current compile buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    */

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error growing current compile buffer case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 2983);

	dg_forthdo(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DO growing current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_compilecallcorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DO growing current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    /*
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcompilebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DO growing current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DO growing current compile buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    */

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error doing begin case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthdo(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdoname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DO error doing begin case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbeginname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DO error doing begin case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthdo(&BHarrayhead);  

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - got an error \n");
	}

	length2 = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	if (length2 != dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID))
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - BEGIN offset incorrect\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - data stack not empty\n");
	}

    /*
	// for gcc FreeBSD's wierdness with compiling comparisons of function returns 
	length = length +28;

	if (length != dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID))
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - buffer not grown\n");
	}

	// for gcc FreeBSD's wierdness with compiling comparisons of function returns 
	length = length - 28;

	if (dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, length) != 0x082574FF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - first byte of compiled code missing\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_DATASPACE_BUFFERID, length + 27) != 0x04)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - last byte of compiled code missing\n");
	}
    */

    // dg_compilecallcore uses shorter call opcodes than original compile do code
    // for gcc FreeBSD's wierdness with compiling comparisons of function returns 
	/*
	length = length +26;

	if (length != dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID))
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - buffer not grown\n");
	}

	// for gcc FreeBSD's wierdness with compiling comparisons of function returns 
	length = length - 26;

	if (dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, length) != 0xB80875FF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - first byte of compiled code missing\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_DATASPACE_BUFFERID, length + 25) != 0x04)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! DO success case - last byte of compiled code missing\n");
	}
	 */

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthdoes ()
{
    Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 mycurrentvariablebuffer;
	UINT64 myvariableoffset;
	UINT64 mycurrentcompilebuffer;
	UINT64 mystartoffset;
	
	UINT64 mydefinition;
    UINT64 mywordlist;
	
	UINT64 x;
    
    const char* pError;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing DOES\n");
	
	// success case changing compile type of a VARIABLE
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);
    
    // dg_initwordlists(&BHarrayhead); // for dg_forthqueryclearlocals
    
    // for dg_forthqueryclearlocals
    mywordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, mywordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - error setting current compile wordlist\n");
        return;
    }
    
    
    mywordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - error making new wordlist\n");
		return;
	}
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, mywordlist);
    
    if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - error setting current compile wordlist\n");
		return;
	}
    
	mycurrentvariablebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not get current new variable buffer\n");
		return;
	}
	
	myvariableoffset = dg_getbufferlength(&BHarrayhead, mycurrentvariablebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not get current new variable buffer's length\n");
		return;
	}
	
	// create a new variable
	mydefinition = dg_createvariabledef (&BHarrayhead, (unsigned char*)"PMYTESTVARIABLE", 15);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not create a new variable\n");
		return;
	}
	
	dg_pushbufferuint64 (&BHarrayhead, mycurrentvariablebuffer, 0x12345678);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not put a value into the new variable\n");
		return;
	}	
	
	// does is a compiling word
	// now compile a forth routine to change the compile type of the latest defined word to do whatever is compiled after the DOES
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compileinitlocals (&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not init locals\n");
		return;
	}
	
	dg_forthdoes (&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE  - could not do DOES\n");
		return;
	}
	
	// does compiles exit locals for the current forth routine and compiles init locals for the new compile type routine
	
	// compiling a forth routine that does: @ 1+
	//   which in C is:
	//     given a pointer to the variable on the data stack,
    //     remove the pointer from the data stack,
	//     get the UINT32 data at that pointer to the data stack
	//     add 1 to that data on the data stack
	
	dg_compilecallcore (&BHarrayhead, (UINT64)&dg_forthfetch);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not compile @\n");
		return;
	}
	
	dg_compilecallcore (&BHarrayhead, (UINT64)&dg_forthoneplus);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not compile 1+\n");
		return;
	}
		
	dg_compileexitlocals(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - could not compile exit locals\n");
		return;
	}
	
	// now call the routine which will change the latest definition's compile type
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE  - got an error calling the subroutine, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
		return;
	}
	
	// now I'm gonna execute the new definition.. it no longer has state behavior and will always do @ 1+
	//  this is the same as if the definition's name PMYTESTVARIABLE was parsed from the script
	dg_executedefinition(&BHarrayhead, mydefinition);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE  - got an error executing the variable\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID); // value of test variable + 1
	
	if (x != 0x12345679)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE - got wrong value for result, expected 0x12345678 got ");
		dg_writestdoutuint64tohex(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	// success case changing compile type of a VARIABLE to c routines
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);
    
    // dg_initwordlists(&BHarrayhead); // for dg_forthqueryclearlocals
    
    // for dg_forthqueryclearlocals
    mywordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, mywordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - error setting current compile wordlist\n");
        return;
    }
    
    mywordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not make new wordlist\n");
		return;
	}
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, mywordlist);
    
    if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - error setting current compile wordlist\n");
		return;
	}
	
	mycurrentvariablebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not get current new variable buffer\n");
		return;
	}
	
	myvariableoffset = dg_getbufferlength(&BHarrayhead, mycurrentvariablebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not get current new variable buffer's length\n");
		return;
	}
	
	// create a new variable
	mydefinition = dg_createvariabledef (&BHarrayhead, (unsigned char*)"PMYTESTVARIABLE", 15);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not create a new variable\n");
		return;
	}
	
	dg_pushbufferuint64 (&BHarrayhead, mycurrentvariablebuffer, 0x12345678);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not put a value into the new variable\n");
		return;
	}	
	
	// does is a compiling word
	// now compile a forth routine to change the compile type of the latest defined word to do whatever is compiled after the DOES
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(
        &BHarrayhead,
        mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not get current compile buffer's length\n");
		return;
	}
	
	dg_compileinitlocals (&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routines - could not init locals\n");
		return;
	}
	
	dg_forthdoes (&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routine - could not do DOES\n");
		return;
	}
	
	// does compiles exit locals for the current forth routine and compiles init locals for the new compile type routine
	
	// compiling a c routine that increments the value of the variable, 
	//   which in C is:
	//     given a pointer to the variable on the data stack,
    //     remove the pointer from the data stack,
	//     get the UINT32 data at that pointer to the data stack
	//     add 1 to that data on the data stack
	
	dg_compilealignretstack(&BHarrayhead, 2);
    dg_compilentoparameter (
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        1);
//	dg_compilepushntoret(&BHarrayhead, DG_DATASTACK_BUFFERID);
	//dg_compilepushparametertoret(&BHarrayhead); // pBHarrayhead
    dg_compilepushpBHarrayheadtoret(&BHarrayhead);
	dg_compilecalladdress(&BHarrayhead, (UINT64)(&dg_popbufferuint64));
//	dg_compiledropparametersfromret (&BHarrayhead, 2);
//	dg_compileundoalignretstack(&BHarrayhead);
	
	// eax will have value of the pointer
	// compile inc [eax] opcode = ff /0 ... mode = 0 reg/n = 0 reg/m = 0 so...
	dg_pushbufferbyte(&BHarrayhead, mycurrentcompilebuffer, 0xff);
	dg_pushbufferbyte(&BHarrayhead, mycurrentcompilebuffer, 0);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routine - could not compile compiletype subroutine\n");
		return;
	}
	
	dg_compileexitlocals(&BHarrayhead);
	
	// now call the routine which will change the latest definition's compile type
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routine  - got an error calling the subroutine\n");
		return;
	}
	
	// now I'm gonna execute the new definition.. it no longer has state behavior and will always do @ 1+
	//  this is the same as if the definition's name PMYTESTVARIABLE was parsed from the script
	dg_executedefinition(&BHarrayhead, mydefinition);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routine  - got an error executing the variable\n");
		return;
	}
	
	x = dg_getbufferuint64(&BHarrayhead, mycurrentvariablebuffer, myvariableoffset); // value of test variable + 1
	
	if (x != 0x12345679)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing DOES changing compile type of a VARIABLE to c routine - got wrong value for result, expected 0x12345678 got ");
		dg_writestdoutuint64tohex(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdot ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing .\n");

	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nYou should see '-342 ' >>>");
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-342);
	dg_forthdot(&BHarrayhead);
	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthstarslash()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing */\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */ (dg_forthstarslash) error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthstarslash(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstarslashname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */  error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */  error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */  error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */ (dg_forthstarslash) underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthstarslash(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstarslashname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */ underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */ underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 100 * 22 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */ (dg_forthstarslash) 22 * 100 / 2 success case - error count not 0");
	}

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
	if (testint != 1100)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */ (dg_forthstarslash) 22 * 100 / 2 success case - got wrong answer, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */ (dg_forthstarslash) 22 * 100 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -2 * -5 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */ (dg_forthstarslash) -2 * -5 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 5)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */ (dg_forthstarslash) -2 * -5 / 2 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */ (dg_forthstarslash) -2 * -5 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 3 * -7 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 3 * -7 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 21)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 3 * -7 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 3 * -7 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 1 * -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 1 * -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 1 * -1 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 1 * -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65535 * -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 65535 * -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65535)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 65535 * -1 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 65535 * -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65536 * -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 65536 * -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65536)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 65536 * -1 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 65536 * -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 * 0x100000000 / 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x100000000 * 0x100000000 / 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)  // overflow
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x10000000 * 0x10000000 / 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x10000000 * 0x10000000 / 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 * 0x100000000 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x100000000 * 0x100000000 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)  // overflow
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x10000000 * 0x10000000 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x1000 * 0x1000 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 * 0x100000000 / -1 b
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x100000000 * 0x100000000 / -1 b success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)  // overflow
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x100000000 * 0x100000000 / -1 b success case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 55)  
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x100000000 * 0x100000000 / -1 b success case - data stack corrupted 55 != \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! * (dg_forthstarslash) 0x100000000 * 0x100000000 / -1 b success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthstarslashmod()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing */MOD\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthstarslashmod(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstarslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthstarslashmod(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstarslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 100 * 22 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 22 * 100 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 1100)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 22 * 100 / 2 success case - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 22 * 100 / 2 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 22 * 100 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -2 * -5 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) -2 * -5 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 5)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) -2 * -5 / 2 success case - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) -2 * -5 / 2 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) -2 * -5 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 3 * -7 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 3 * -7 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 21)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 3 * -7 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 3 * -7 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 3 * -7 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 1 * -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 1 * -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 1 * -1 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 1 * -1 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 1 * -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65535 * -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65535 * -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65535)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65535 * -1 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65535 * -1 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65535 * -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65536 * -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65536 * -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65536)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65536 * -1 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65535 * -1 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 65536 * -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 * 0x100000000 / 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x100000000 * 0x100000000 / 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)  // overflow
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x100000000 * 0x100000000 / 1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x100000000 * 0x100000000 / 1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x100000000 * 0x100000000 / 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 * 0x100000000 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthstarslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x100000000 * 0x100000000 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)  // overflow with negative quotient
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x100000000 * 0x100000000 / -1 success case - got wrong answer \n");
	}
    
	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x7FFFFFFFFFFFFFFF) // remainder gets same sign as numerator
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x100000000 * 0x100000000 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! */MOD (dg_forthstarslashmod) 0x10000000 * 0x10000000 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthzeroless()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 0<\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthzeroless(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzerolessname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthzeroless(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzerolessname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF000000000000FF 0<
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthzeroless(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 0<
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthzeroless(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 0< 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthzeroless(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0< 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthzeroless(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 0 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 0 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0< 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthzeroequals()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 0=\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthzeroequals(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzeroequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthzeroequals(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzeroequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF 0= 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthzeroequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 0=
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthzeroequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 0= 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthzeroequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0= 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthzeroequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 0 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 0 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0= 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthoneplus()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 1+\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthoneplus(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthoneplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthoneplus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthoneplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF000000000000FF 1+
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthoneplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFF00000000000100)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 1+
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthoneplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 1+ 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthoneplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 6 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1+ 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthoneminus()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 1-\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthoneminus(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthoneminusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthoneminus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthoneminusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- parameters missing case - got wrong error on top");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- parameters missing case - got wrong error 1 below top");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF000000000000FF 1-
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthoneminus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFF000000000000FE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 1-
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthoneminus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 1- 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthoneminus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 4 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1- 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwostore()
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

	UINT64 testint2[2];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2!\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwostore(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwostorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 48778);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3984);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! underflow case - unable to initialize data stack");
		return;
	}

	dg_forthtwostore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwostorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	//bad address error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 48778);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3984);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! bad address case - unable to initialize data stack");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is a bad address

	dg_forthtwostore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwostorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! bad address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_badmemoryerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! bad address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x9ABCDEF0); // lo
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x12345678); // hi

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint2);

	dg_forthtwostore(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! success case - error count not 0 got \n");
	}

	if (testint2[0] != 0x12345678) // hi
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! success case - got wrong answer hi \n");
	}

	if (testint2[1] != 0x9ABCDEF0) // lo
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! success case - got wrong answer lo \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2! success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwostar()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2*\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwostar(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwostarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthtwostar(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwostarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF000000000000FF 2*
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthtwostar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFE000000000001FE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* 0xFF000000000000FF success case - got wrong answer, expected 0xFE00000000000001FE, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 2*
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthtwostar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 2* 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthtwostar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 10 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2* 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwoslash()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing 2/\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwoslash(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwoslashname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2/ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2/ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2/ error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthtwoslash(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwoslashname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2/ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2/ parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF000000000000FF 2/
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthtwoslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFF8000000000007F)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 2/
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthtwoslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 2/ 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthtwoslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 2/ 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwofetch()
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

	UINT64 testint2[2];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2@\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwofetch(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwofetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthtwofetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwofetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	//grow data stack error
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ grow data stack case - unable to initialize data stack");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint2);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = sizeof (UINT64);
	pBH->growby = sizeof (UINT64);
	pBH->maxsize = sizeof (UINT64);
	pBH->nextunusedbyte = sizeof (UINT64);

	// could check where stack is corrupt, with just under 1 element

	dg_forthtwofetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwofetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ grow data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ grow data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    
    // pError = dg_poperror(&BHarrayhead);

	// if (pError != dg_outofmemoryerror)
	// {
	//    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ grow data stack case - got wrong error 2 below top, got ");
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	// }
    

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	//bad address error
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ bad address case - unable to initialize data stack");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is a bad address

	// could check where stack is corrupt, with just under 1 element

	dg_forthtwofetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwofetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ bad address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ bad address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_badmemoryerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ bad address case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	testint2[0] = 0x12345678; // hi
	testint2[1] = 0x9ABCDEF0; // lo

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint2);

	dg_forthtwofetch(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x12345678) // hi
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ success case - got wrong answer hi \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x9ABCDEF0) // lo
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ success case - got wrong answer lo \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2@ success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwodrop()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2DROP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwodrop(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwodropname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP underflow case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthtwodrop(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwodropname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9834);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9834);

	dg_forthtwodrop(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP success case - error count not 0 got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DROP success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwodup()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2DUP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwodup(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwodupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP underflow case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthtwodup(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwodupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// grow error case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = 2* sizeof (UINT64);
	pBH->growby = 2* sizeof (UINT64);
	pBH->maxsize = 2* sizeof (UINT64);
	pBH->nextunusedbyte = 2* sizeof (UINT64);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP grow error case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthtwodup(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwodupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP grow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP grow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9834);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2304);

	dg_forthtwodup(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2304)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP success case - got wrong number on top, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9834)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP success case - got wrong number on 2nd, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2304)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP success case - got wrong number on 3rd, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9834)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP success case - got wrong number on 4th, got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwoover()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2OVER\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwoover(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwoovername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER underflow case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthtwoover(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwoovername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// grow error case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = 4* sizeof (UINT64);
	pBH->growby = 4* sizeof (UINT64);
	pBH->maxsize = 4* sizeof (UINT64);
	pBH->nextunusedbyte = 4* sizeof (UINT64);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER underflow case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthtwoover(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwoovername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER grow error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER grow error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9834);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2304);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9023984);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 385873);

	dg_forthtwoover(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2DUP success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2304)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER success case - got wrong number on top, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9834)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER success case - got wrong number on 2nd, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 385873)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER success case - got wrong number on 3rd, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9023984)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER success case - got wrong number on 4th, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2304)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER success case - got wrong number on 5th, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9834)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER success case - got wrong number on 6th, got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2OVER success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtwoswap()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2SWAP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtwoswap(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwoswapname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP underflow case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthtwoswap(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtwoswapname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9834);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2304);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9023984);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 385873);

	dg_forthtwoswap(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2304)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP success case - got wrong number on top, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9834)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP success case - got wrong number on 2nd, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 385873)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP success case - got wrong number on 3rd, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9023984)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP success case - got wrong number on 4th, got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2SWAP success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthcolon()
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
	UINT64 cibufid = 0;

	UINT64 wordlist = 0;
	UINT64 definition = 0;
	Definitionheader* pdefinition = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing :\n");
#ifndef DGLU_NO_DIAPER
	// error getting current compile buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthcolon(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error getting current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error getting current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting interpret buffer id case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 1288);

	dg_forthcolon(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error getting pointer to current interpret buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error getting pointer to current interpret buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// name length = 0 error 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthcolon(&BHarrayhead); // current interpret buffer is empty so namelength will be 0

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : no name error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_wordlength0error)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : no name error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error creating definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	//dg_freebuffer(&BHarrayhead, DG_DEFINITION_BUFFERID);

	dg_forthcolon(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error creating definintion case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createsubthreaddefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error creating definintion case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// if the code can get the current interpret buffer, I don't know how to get an error from setting the state variable

	// push colon sys error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthcolon(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error pushing colonsys case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error pushing colonsys case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : error pushing colonsys case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	dg_forthleftbracket(&BHarrayhead);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	//length = dg_getbufferlength(&BHarrayhead, DG_DEFINITION_BUFFERID);

	dg_forthcolon(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != colonsysmarker)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - colonsys marker missing\n");
	}

	//length = length + sizeof(Definitionheader);

	//if (length != dg_getbufferlength(&BHarrayhead, DG_DEFINITION_BUFFERID))
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - length of definition buffer did not increase by correct amount\n");
	//}

	//pbuffer = dg_getpbuffer(&BHarrayhead, DG_DEFINITION_BUFFERID, &plength);

	//definition = (((*plength) / sizeof(Definitionheader)) - 1);

	//if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != definition)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - latest definition part of colon sys missing from data stack\n");
	//}


   	//pbuffer = dg_getpbuffersegment(&BHarrayhead, DG_DEFINITION_BUFFERID, definition * sizeof(Definitionheader), sizeof(Definitionheader));

	//pdefinition = (Definitionheader*)pbuffer;
    
    definition = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (definition != DG_ENDOFLIST)
    {
        pdefinition = dg_getpdefinition(&BHarrayhead, definition);

        if (pdefinition->compileroutineoffset != (UINT64)&dg_forthdocompiletypesubroutine)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - new definition not a subroutine threaded definition\n");
        }
    }
    else
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success case - had problem getting latest definition.\n");
    }

	//pbuffer = dg_getplstring(&BHarrayhead, nameoffsetbufferid, namestringbufferid, definition, &length);

	//if (pbuffer[0] != 't')
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - name of definition incorrect\n");
	//}

	//if (length != 8)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - length of definition's name incorrect\n");
	//}

	//if (pbuffer[7] != 'e')
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! : success case - end of definition name incorrect\n");
	//}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


}



void testdg_forthsemicolon()
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

	UINT64 ccbufid = 0;
	UINT64 cibufid = 0;
	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	UINT64 wordlist = 0;

	UINT64 length = 0;

  //  unsigned char cterm = '\0';

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing ;\n");
#ifndef DGLU_NO_DIAPER
	// error compiling return case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ; error compiling return case - unable to initialize error stack\n");
		return;
	}

	dg_forthsemicolon(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsemicolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error compiling return case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthqueryclearlocalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error compiling return case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// if compileret worked, then I dont know how to get an error setting the state 
	//  because compileret gets the currentcompilebuffer

	// error getting a pointer to the data stack case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
 
    dg_inithlists(&BHarrayhead);   
    
    // dg_initwordlists(&BHarrayhead); // for dg_forthqueryclearlocals
    
    wordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error compiling return case - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, wordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error compiling return case - error setting current compile wordlist\n");
        return;
    }

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthsemicolon(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsemicolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// data stack underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
 
    dg_inithlists(&BHarrayhead);   
    
    // dg_initwordlists(&BHarrayhead); // for dg_forthqueryclearlocals
    wordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error data stack underflow case - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, wordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error data stack underflow case - error setting current compile wordlist\n");
        return;
    }

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthsemicolon(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsemicolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error data stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error data stack underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// missing colonsys case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
 
    dg_inithlists(&BHarrayhead);
    
    // dg_initwordlists(&BHarrayhead); // for dg_forthqueryclearlocals
    wordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; missing colonsys case - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, wordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; missing colonsys case - error setting current compile wordlist\n");
        return;
    }

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthsemicolon(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsemicolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; missing colonsys case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_colonsysmissingerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; missing colonsys case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting currentcompilewordlist
      // removing test because ?CLEAR-LOCALS uses stuff declared after current compile wordlist
	//dg_initbuffers(&BHarrayhead);

	//dg_initvariables(&BHarrayhead);

	//dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	//dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, colonsysmarker);

	//ccbufid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

	//dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, ccbufid); // need to move compilebuffer for this test

	//pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASPACE_BUFFERID] );
	
	//pBH->size = currentcompilewordlist;
	//pBH->growby = currentcompilewordlist;
	//pBH->maxsize = currentcompilewordlist;
	//pBH->nextunusedbyte = currentcompilewordlist;

	//dg_forthsemicolon(&BHarrayhead); 

	//pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_forthsemicolonname)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error getting current compile wordlist case - got wrong error on top, got ");
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

    //pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_forthpcurrentcreatewordlistname)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error getting current compile wordlist case - got wrong error 1 below top, got ");
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

	//dg_clearerrors(&BHarrayhead);

	//dg_freeallbuffers(&BHarrayhead);

	// error linking definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
 
    dg_inithlists(&BHarrayhead);   
    
    // dg_initwordlists(&BHarrayhead); // for dg_forthqueryclearlocals
    wordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error linking definition  case - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, wordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error linking definition  case - error setting current compile wordlist\n");
        return;
    }

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9999);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, colonsysmarker);

	dg_forthsemicolon(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsemicolonname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error linking definition  case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_linkdefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; error linking definition  case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);
    
    // dg_initwordlists(&BHarrayhead); // for dg_forthqueryclearlocals
    wordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; success case - error making new wordlist\n");
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid, wordlist);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ; success case - error setting current compile wordlist\n");
        return;
    }

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	dg_forthleftbracket(&BHarrayhead);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	dg_forthcolon(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ; success case - unable to initialize definition with :\n");
		return;
	}

    length = dg_getbufferlength(&BHarrayhead, ccbufid);

	dg_forthsemicolon(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ; success case - got an error\n");
        dg_forthdoterrors(&BHarrayhead);
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ; success case - colonsys not removed from data stack\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, ccbufid, &plength);

	if (length == *plength)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ; success case - current compile buffer length did not increase");
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}

	// could try to test exit function here
}


void testdg_forthlessthan()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing <\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthlessthan(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlessthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthlessthan(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlessthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 < 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthlessthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < 65536 < 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < 65536 < 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < 65536 < 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// dg_success case -1 < 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthlessthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < -1 < 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < -1 < 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < -1 < 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 < 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthlessthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < 5 < 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < 5 < 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! < 5 < 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthlessthannumbersign()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing <#\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to pad case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <# error getting pointer to pad case - unable to initialize error stack");
		return;
	}

	dg_forthlessthannumbersign(&BHarrayhead); // error because there is no pad yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlessthannumbersignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <# error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthholdbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <# error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_HOLD_BUFFERID, 23984); // make pad length not 0

	dg_forthlessthannumbersign(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <# success case - error count not 0");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_HOLD_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <# success case - pad length not 0");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthequals()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing =\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthequals(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthequals(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 = 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = 65536 = 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = 65536 = 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = 65536 = 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 = 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = -1 = 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = -1 = 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = -1 = 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 = 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = 5 = 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = 5 = 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! = 5 = 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthgreaterthan()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing >\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthgreaterthan(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgreaterthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthgreaterthan(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgreaterthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 > 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthgreaterthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > 65536 > 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > 65536 > 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > 65536 > 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 > 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthgreaterthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > -1 > 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > -1 > 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > -1 > 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 > 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthgreaterthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > 5 > 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > 5 > 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! > 5 > 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtobody ()
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
	unsigned char* pbuffer = NULL;

	UINT64 wordlist = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing >BODY\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to data stack case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthtobody(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtobodyname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 32980); // id of a buffer that isn't allocated yet

	dg_forthtobody(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtobodyname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// dg_getpdefinition error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2303);

	dg_forthtobody(&BHarrayhead); // no definitions declared

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtobodyname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY dg_getpdefinition error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpdefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY dg_getpdefinition error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// dg_getpbufferoffset error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_newword(
		&BHarrayhead,
		0,
		0,
		3908, 
		0,
		DG_CORE_BUFFERID,
		(UINT64)"hi",
		2);

	dg_forthtobody(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtobodyname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY dg_getpbufferoffset error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffersegmentname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY dg_getpbufferoffset error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// if dg_growbuffer worked, don't know how to get error from dg_getpbuffer
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	dg_createvariabledef(&BHarrayhead, (unsigned char*)"hi", 2);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthtobody(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY success case - got an error \n");
		return;
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	if (testint != (UINT64)(pbuffer + *plength))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY success case - got wrong address\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >BODY success case - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthtoin ()
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

	UINT64 bufid = 0;
	UINT64* poffset = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing >IN\n");
#ifndef DGLU_NO_DIAPER
	// error getting current interpret buffer id case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error getting current interpret buffer id case - unable to initialize error stack");
		return;
	}

	dg_forthtoin(&BHarrayhead); // error because there is no data space buffer yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtoinname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error getting current input buffer id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentinputbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error getting current input buffer id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error getting current input buffer id case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to current input buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, 32980); // id of a buffer that isn't allocated yet

	dg_forthtoin(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtoinname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentinputbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error growing data stack - why didn't I just use dg_pushbufferuint64?
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthtoin(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtoinname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error growing data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error growing data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN error growing data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// if dg_growbuffer worked, don't know how to get error from dg_getpbuffer

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthtoin(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN dg_success case - got an error \n");
		return;
	}

	poffset = (UINT64*)dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (*poffset != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN success case - expected input buffer to be empty\n");
	}

	bufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, bufid, 9, (unsigned char*)"hi )nicd");

	dg_forthparen(&BHarrayhead);

	if (*poffset != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN success case - expected input buffer to have 4 in it\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >IN success case - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);	
}


void testdg_forthtonumber()
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
	UINT64 addr = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing >NUMBER\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtonumber(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtonumbername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >>NUMBER error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >>NUMBER error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >>NUMBER error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER parameters missing case - unable to initialize data stack");
		return;
	}

	dg_forthtonumber(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtonumbername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error getting base case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting base case - unable to initialize data stack");
		return;
	}

	dg_forthtonumber(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtonumbername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting base case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting base case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting base case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// error base too low case
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 1);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting base case - unable to initialize data stack");
		return;
	}

	dg_forthtonumber(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtonumbername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting base case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_basetoolowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER error getting base case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0 "1234" 4
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);
	dg_forthdecimal(&BHarrayhead);

	addr = (UINT64)"1234";

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, addr);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthtonumber(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 1234 4 success case - error count not 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 1234 4 success case - got wrong number of characters left \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != addr + 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 1234 4 success case - got wrong address out \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 1234 4 success case - got wrong answer hi\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1234)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 1234 4 success case - got wrong answer lo\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 1234 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 15 "1294" 4
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);
	dg_forthdecimal(&BHarrayhead);

	addr = (UINT64)"1294";

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 15);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, addr);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthtonumber(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 15 1294 4 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 15 1294 4 success case - got wrong number of characters left \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != addr + 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 15 1294 4 success case - got wrong address out \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 15 1294 4 success case - got wrong answer hi \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 151294)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 15 1294 4 success case - got wrong answer lo \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 15 1294 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0 "12A4" 4
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);
	dg_forthdecimal(&BHarrayhead);

	addr = (UINT64)"12A4";

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, addr);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthtonumber(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12A4 4 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12A4 4 success case - got wrong number of characters left \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != addr + 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12A4 4 success case - got wrong address out \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12A4 4 success case - got wrong answer hi\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12A4 4 success case - got wrong answer lo\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12A4 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0 "12F4" 4
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);
	dg_forthhex(&BHarrayhead);

	addr = (UINT64)"12F4";

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, addr);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthtonumber(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12F4 4 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12F4 4 success case - got wrong number of characters left \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != addr + 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12F4 4 success case - got wrong address out \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12F4 4 success case - got wrong answer hi\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x12F4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12F4 4 success case - got wrong answer lo\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 12F4 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 "12G4" 4
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);
	dg_forthhex(&BHarrayhead);

	addr = (UINT64)"12G4";

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, addr);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthtonumber(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 00 12G4 4 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12G4 4 success case - got wrong number of characters left \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != addr + 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12G4 4 success case - got wrong address out \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x0)
	{
	    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12G4 4 success case - got wrong answer hi \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12G4 4 success case - got wrong answer lo \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12G4 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0 "12//4" 4
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);
	dg_forthhex(&BHarrayhead);

	addr = (UINT64)"12//4";

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, addr);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthtonumber(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12s4 4 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12s4 4 success case - got wrong number of characters left \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != addr + 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12s4 4 success case - got wrong address out \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12s4 4 success case - got wrong answer hi\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12s4 4 success case - got wrong answer lo\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >NUMBER 0 0 12s4 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthtor()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing >R\n");
#ifndef DGLU_NO_DIAPER
	// error popping datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error popping data stack case - unable to initialize error stack");
		return;
	}

	dg_forthtor(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtorname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing rstack case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	dg_freebuffer(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error pushing rstack case - unable to initialize data stack");
		return;
	}

	dg_forthtor(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtorname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error pushing rstack case  - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error pushing rstack case  - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R error pushing rstack case  - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	dg_forthtor(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 0x55667788)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R success case - got wrong number of characters left \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R success case - data  stack not empty after calculation\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R success case - rstack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthquestiondup()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ?DUP\n");
#ifndef DLGU_NO_DIAPER	
	// error popping datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error popping data stack case - unable to initialize error stack");
		return;
	}

	dg_forthquestiondup(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthquestiondupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing data stack case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = sizeof(UINT64);
	pBH->growby = sizeof(UINT64);
	pBH->maxsize = sizeof(UINT64);
	pBH->nextunusedbyte = sizeof(UINT64);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error pushing rstack case - unable to initialize data stack");
		return;
	}

	dg_forthquestiondup(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthquestiondupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error pushing rstack case  - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error pushing rstack case  - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP error pushing rstack case  - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthquestiondup(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP 0 success case - error count not 0");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != sizeof(UINT64)) // dg_popbufferuint64 returns 0 on error so we need to check length first
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP 0 success case - data  stack not empty after calculation\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0) 
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP 0 success case - got wrong number number \n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case not 0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthquestiondup(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP not 0 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP not 0 success case - got wrong number number \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP not 0 success case - got wrong number number \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ?DUP not 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthfetch()
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

	UINT64 testint2[2];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing @\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthfetch(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	//bad address error
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ bad address case - unable to initialize data stack");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is a bad address

	// could check where stack is corrupt, with just under 1 element

	dg_forthfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ bad address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ bad address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_badmemoryerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ bad address case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	testint2[0] = 0x12345678; 

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint2);

	dg_forthfetch(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x12345678) 
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ success case - got wrong answer hi \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! @ success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthabs()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ABS\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthabs(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthabsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthabs(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthabsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF ABS 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthabs(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x00FFFFFFFFFFFF01)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 ABS
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthabs(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 ABS 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthabs(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ABS 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthaccept()
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

	unsigned char testbuff[100];
	UINT64 i = 0;

    unsigned char c;
    UINT64 stdinfileid;
    UINT64 numread;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ACCEPT\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthaccept(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthacceptname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept underflow case - unable to initialize data stack");
		return;
	}

	dg_forthaccept(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthacceptname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// maxlength <= 0 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept maxlength <= 0 case case - unable to initialize data stack");
		return;
	}

	dg_forthaccept(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthacceptname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept maxlength <= 0 case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_signedlengthlessthan0error)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept maxlength <= 0 case case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// bad address case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept bad address case - unable to initialize data stack");
		return;
	}

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nPlease type in a character and press return\n");

	dg_forthaccept(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthacceptname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept bad address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_putbytename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept bad address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    c = 0;
    dg_gethstdin(
        &BHarrayhead,
        &stdinfileid, 
        dg_success);

	// need to clear os input buffer
	while (c != 10)
	{
        dg_readfile(
            &BHarrayhead,
            stdinfileid,
            &c,
            1,
            0,
            &numread,
            dg_success);
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nPlease type in 15 characters - no X's, back up 10, press return\n");

	for (i=0; i < 80; i++)
	{
		testbuff[i] = 'X';
	}

	dg_forthaccept(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept success case - didn't get exactly 5 characters \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept success case - data  stack not empty after calculation\n");
	}

	if (testbuff[0] == 'X')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept success case - buf[0] not changed\n");
	}

	if (testbuff[4] == 'X')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept success case - buf[4] not changed\n");
	}

	if (testbuff[5] != 'X')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthaccept success case - buf[5] was changed\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

}


void testdg_forthalign()
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
	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;
    UINT64 x;


	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ALIGN\n");
#ifndef DGLU_NO_DIAPER
	// error getting current data space buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting current data space buffer id case - unable to initialize error stack\n");
		return;
	}

	dg_forthalign(&BHarrayhead); // error because there is no data space buffer yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthalignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting current data space buffer id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting current data space buffer id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting current data space buffer id case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to the current data space buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, 3984);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting pointer to current data space buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthalign(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthalignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting pointer to current data space buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting pointer to current data space buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error getting pointer to current data space buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error growing the current data space buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	dg_pushbufferbyte(&BHarrayhead, DG_DATASPACE_BUFFERID, 88); // to make data space buffer not be UINT64 aligned

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASPACE_BUFFERID] );
	
	pBH->size = pBH->nextunusedbyte;
	pBH->growby = pBH->nextunusedbyte;
	pBH->maxsize = pBH->nextunusedbyte;

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error growing current data space buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthalign(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthalignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error growing current data space buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error growing current data space buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN error growing current data space buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case already aligned
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case already aligned - unable to initialize error stack\n");
		return;
	}
    
    x = *plength % sizeof(UINT64);
    
    if (x != 0)
    {
        dg_growbuffer(
            &BHarrayhead,
            DG_DATASPACE_BUFFERID,
            sizeof(UINT64) - x,
            &pError,
            false);
        
        if (pError != dg_success)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case already aligned - unable to grow buffer to aligned position\n");
            return;
        }
    }
    
    x = *plength % sizeof(UINT64);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case already aligned - alignment of unaligned buffer didn't work\n");
        return;
    }
    
    x = *plength;

	dg_forthalign(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case already aligned - got an error\n");
	}

	if (*plength != x)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case already aligned - buffer length changed\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case +1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +1 - unable to initialize error stack\n");
		return;
	}
    
    x = *plength % sizeof(UINT64);
    
    if (x != 0)
    {
        dg_growbuffer(
            &BHarrayhead,
            DG_DATASPACE_BUFFERID,
            sizeof(UINT64) - x,
            &pError,
            false);
        
        if (pError != dg_success)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case aligned +1 - unable to grow buffer to aligned position\n");
            return;
        }
    }
    
    x = *plength % sizeof(UINT64);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case aligned +1 - alignment of unaligned buffer didn't work\n");
        return;
    }
    
    (*plength)++;
    x = *plength;

	dg_forthalign(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +1 - got an error\n");
	}

	if (*plength != (x + (sizeof(UINT64) - 1)))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +1 - buffer length changed\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case +2
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +2 - unable to initialize error stack\n");
		return;
	}
    
    x = *plength % sizeof(UINT64);
    
    if (x != 0)
    {
        dg_growbuffer(
            &BHarrayhead,
            DG_DATASPACE_BUFFERID,
            sizeof(UINT64) - x,
            &pError,
            false);
        
        if (pError != dg_success)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case aligned +2 - unable to grow buffer to aligned position\n");
            return;
        }
    }
    
    x = *plength % sizeof(UINT64);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case aligned +2 - alignment of unaligned buffer didn't work\n");
        return;
    }
    
    (*plength)++;
    (*plength)++;
    x = *plength;

	dg_forthalign(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +2 - got an error\n");
	}

	if (*plength != ((x + (sizeof(UINT64) - 2))))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +2 - buffer length changed\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case +3
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	*plength = 13 * sizeof(UINT64)+3;

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +3 - unable to initialize error stack\n");
		return;
	}

	dg_forthalign(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +3 - got an error\n");
	}

	if (*plength != 14 * sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGN success case +3 - buffer length changed\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthaligned()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ALIGNED\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthaligned(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthalignedname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthaligned(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthalignedname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF ALIGNED 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthaligned(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 0xFF00000000000100 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFF00000000000100)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 0xFF00000000000100 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 0xFF00000000000100 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 ALIGNED
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthaligned(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 ALIGNED 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthaligned(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 8 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 12 ALIGNED 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 12);

	dg_forthaligned(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 12 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 16 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 12 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALIGNED 12 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthallot()
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

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ALLOT\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthallot(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthallotname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT underflow case - unable to initialize data stack\n");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthallot(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthallotname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting current variable buffer
	dg_initbuffers(&BHarrayhead);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 30);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT getting current variable buffer case - unable to initialize data stack\n");
		return;
	}

	dg_forthallot(&BHarrayhead); // variable buffer not initialized... so...

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthallotname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT getting current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT getting current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT getting current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error growing current variable buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 30);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, 389);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT growing current variable buffer case - unable to initialize data stack\n");
		return;
	}

	dg_forthallot(&BHarrayhead); 
	
	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthallotname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT growing current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT growing current variable buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT growing current variable buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error shrinking current variable buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-30);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, 389);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT shrinking current variable buffer case - unable to initialize data stack\n");
		return;
	}

	dg_forthallot(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthallotname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT shrinking current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT shrinking current variable buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_shrinkbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT shrinking current variable buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    


	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 30);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT dg_success case - unable to initialize data stack");
		return;
	}

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthallot(&BHarrayhead); // variable buffer not initialized... so...

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT success case - got an error \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT success case - data stack not empty\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID) != length + 30)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ALLOT success case - data space buffer not bigger by correct amount\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// could test shrink case
}


void testdg_forthand()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing AND\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthand(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthandname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthand(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthandname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF AND 0x03C003C0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x03C00000000003C0);

	dg_forthand(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND 0xFF000000000000FF AND 0x03C00000000003C0 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x03000000000000C0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND 0xFF000000000000FF AND 0x03C00000000003C0 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND 0xFF000000000000FF AND 0x03C00000000003C0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 AND 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthand(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND -1 AND 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND -1 AND 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND -1 AND 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 AND 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthand(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND 5 AND 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND 5 AND 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! AND 5 AND 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthbase ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing BASE\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE error getting pointer to base variable case - unable to initialize error stack");
		return;
	}

	dg_forthbase(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE error getting pointer to base variable case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffersegmentname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE error getting pointer to base variable case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// push data stack error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE push data stack error case - unable to initialize data stack");
		return;
	}

	dg_forthbase(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead) ;

	if (pError!= dg_forthbasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead) ;

	if (pError!= dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead) ;

	if (pError!= dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE push data stack error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthbase(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != ((UINT64)dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength)) + basevariable)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BASE success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthbegin()
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

	UINT64 ccbufid = 0;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing BEGIN\n");
#ifndef DGLU_NO_DIAPER
	// error getting current compile buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore error current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthbegin(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbeginname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error getting current compile buffer id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcompilebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error getting current compile buffer id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error getting current compile buffer id case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to the current compile buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 398);

	dg_forthbegin(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbeginname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error getting pointer to current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcompilebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error getting pointer to current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error getting pointer to current compile buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing to the data stack case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthbegin(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbeginname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error pushing the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error pushing the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN error pushing the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthbegin(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN dg_success case - got an error\n");
	}

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	// have to do this in 2 steps, gcc for FreeBSD does wrong thing if you do comparison in 1
	length = dg_getbufferlength(&BHarrayhead, ccbufid);

	if (length != dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BEGIN success case - wrong offset pushed to the data stack\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthbl()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing BL\n");
#ifndef DGLU_NO_DIAPER
	// error pushing to the data stack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BL error pushing to the data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthbl(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthblname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BL error pushing to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BL error pushing to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BL error pushing to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthbl(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BL success case - got an error\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != ' ')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BL success case - didn't get space on the data stack\n");
		return;
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! BL success case - data stack not empty after calculations\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthcstore()
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
	unsigned char testchar = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing C!\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthcstore(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore error getting pointer to data stack case - got wrong error  2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// address and maybe data missing case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore address and maybe data missing case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthcstore(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore address and maybe data missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore address and maybe data missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// illegal address error

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1234567812345679);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is an illegal address

	dg_forthcstore(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcstorename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore illegal address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_putbytename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore illegal address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // address and maybe data missing case
    
#endif

    dg_initbuffers(&BHarrayhead);

	// success case
	testchar = 0;

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x45);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testchar);

	dg_forthcstore(&BHarrayhead);

	if (testchar != 0x45)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore success case - number wasn't stored");
	}

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcstore success case - error count not 0");
	}

	dg_clearerrors(&BHarrayhead);

	// cleanup
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthccomma ()
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

	UINT64 bufid = 0;
	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing C,\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthccomma(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthccommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, underflow case - unable to initialize data stack");
		return;
	}

	dg_forthccomma(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthccommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error getting current data space buffer
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, underflow case - unable to initialize data stack");
		return;
	}

	dg_forthccomma(&BHarrayhead); // variables not initialized

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthccommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error getting current data space  buffer id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error getting current data space  buffer id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error getting current data space  buffer id case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error pushing to current variable buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, 3908); // bufferid of nonexistant buffer

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error pushing to current variable buffer case - unable to initialize data stack");
		return;
	}

	dg_forthccomma(&BHarrayhead); // variables not initialized

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthccommaname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error pushing to current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error pushing to current variable buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferbytename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, error pushing to current variable buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); // hopefully currentvariablebuffer is initialized

	bufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65);

	length = dg_getbufferlength(&BHarrayhead, bufid);

	dg_forthccomma(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, 65 success case - error count not 0");
	}

	testint = (UINT64)dg_popbufferbyte(&BHarrayhead, bufid);

	if (testint != 65)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, 65 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, bufid) != length)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C, 65 success case - current variable buffer length not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthcfetch()
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

	unsigned char testint2[2];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing C@\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthcfetch(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ underflow case - unable to initialize data stack");
		return;
	}

	dg_forthcfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	//bad address error
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ bad address case - unable to initialize data stack");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is a bad address

	// could check where stack is corrupt, with just under 1 element

	dg_forthcfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ bad address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbytename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ bad address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case  
	dg_initbuffers(&BHarrayhead);

	testint2[0] = 78; 

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&testint2);

	dg_forthcfetch(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 78) 
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ success case - got wrong answer hi \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! C@ success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthcellplus ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CELL+\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthcellplus(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcellplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthcellplus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcellplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF CELL+ 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthcellplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFF00000000000107)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 CELL+
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthcellplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 CELL+ 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthcellplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 13 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELL+ 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthcells ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CELLS\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthcells(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcellsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dCELLS underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthcells(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcellsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthcells(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS 0 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS 0 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthcells(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthcells(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 40 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CELLS 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthchar ()
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
	UINT64 cibufid = 0;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CHAR\n");
#ifndef DGLU_NO_DIAPER
	// error getting current interpret buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthchar(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error getting current interpret buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error getting current interpret buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pcib
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer,9348);

	dg_forthchar(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	// name length = 0 error 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthchar(&BHarrayhead); // current interpret buffer is empty so namelength will be 0

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR no name error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_nowordfounderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR no name error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// push data stack error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthchar(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error pushing data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error pushing data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR error pushing data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dg_forthchar(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)'t')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR success case - didn't get first character back\n");
	}

	if (length + 9 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR success case - current input offset pointer not after delimiter after first word\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname  after");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	pBH->currentoffset = 8;

	length = pBH->currentoffset;

	dg_forthchar(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)'a')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR success case - didn't get first character back\n");
	}

	if (length + 7 != pBH->currentoffset) // because I set start on character before first word
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR success case 2- current input offset pointer not on delimiter after second word\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthcharplus()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CHAR+\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthcharplus(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthcharplus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 0xFF0000FF CHAR+ 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF0000FF);

	dg_forthcharplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ 0xFF0000FF success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFF000100)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ 0xFF0000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ 0xFF0000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 CHAR+
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthcharplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 CHAR+ 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthcharplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 6 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHAR+ 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthchars()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CHARS\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthchars(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthchars(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcharsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 0xFF0000FF CHARS 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF0000FF);

	dg_forthchars(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS 0xFF0000FF success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFF0000FF)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS 0xFF0000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS 0xFF0000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


	// success case -1 CHARS
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthchars(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


	// success case 5 CHARS 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthchars(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CHARS 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthconstant ()
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

	UINT64 cibufid = 0;

	UINT64 wordlist = 0;
	Definitionheader* pdefinition = NULL;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CONSTANT\n");
#ifndef DGLU_NO_DIAPER
	// error getting current interpret buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthconstant(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthconstantname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT error getting current interpret buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT error getting current interpret buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pcib
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer,9348);

	dg_forthconstant(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthconstantname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	// pop data stack error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer,DG_DATASPACE_BUFFERID);

	dg_forthconstant(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthconstantname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT pop data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT pop data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT pop data stack error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
#endif
	// name length = 0 error 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthconstant(&BHarrayhead); // current interpret buffer is empty so namelength will be 0

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthconstantname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT no name error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_wordlength0error)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT no name error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// name too long error 
	//dg_initbuffers(&BHarrayhead);

	//dg_initvariables(&BHarrayhead);

	//dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	//for (i=0; i < 256; i++)
	//{
	//	dg_pushbufferbyte(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 't');
	//}

	//dg_forthconstant(&BHarrayhead); 

	//pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_forthconstantnonameerror)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT name too long error case - got wrong error \n");
	//}

	//dg_clearerrors(&BHarrayhead);

	//dg_freeallbuffers(&BHarrayhead);

	// error creating constant definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 8, (unsigned char*)"hi there");

	dg_forthconstant(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthconstantname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT error creating constant definition case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createconstantdefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT error creating constant definition case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dg_forthconstant(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT success case - got an error\n");
	}

	if (length + 9 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT success case - current input offset pointer not after delimiter after first word\n");
	}

	pdefinition = dg_getpdefinition(&BHarrayhead, 0);

	if (pdefinition->dataoffset != 2398)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT success case - expected definition dataoffset to be 2398\n");
	}

	// not checking to see if I passed in  pointer to name correctly here

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);	
}


void testdg_forthcount ()
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

	unsigned char testbuff[20];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing COUNT\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthcount(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcountname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_forthcount(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcountname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// bad address case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthcount(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcountname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT bad address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbytename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT bad address case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case COUNT 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);

	testbuff[0] = 0x34;

	dg_forthcount(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x34)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT success case - got wrong address out \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)(testbuff + 1))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT success case - got wrong count out \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! COUNT success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthcr ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CR\n");

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nThis message should continue on the next line >>>");
	dg_forthcr(&BHarrayhead);
	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<< this should be on the next line\n");
}


void testdg_forthcreate ()
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

	UINT64 cibufid = 0;

	UINT64 wordlist = 0;

	Definitionheader* pdefinition = NULL;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CREATE\n");
#ifndef DGLU_NO_DIAPER
	// error getting current interpret buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthcreate(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcreatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE error getting current interpret buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE error getting current interpret buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pcib
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer,9348);

	dg_forthcreate(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcreatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_parsewordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE error getting pointer to current input buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	// name length = 0 error 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthcreate(&BHarrayhead); // current interpret buffer is empty so namelength will be 0

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcreatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE no name error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_wordlength0error)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE no name error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// name too long error 
	//dg_initbuffers(&BHarrayhead);

	//dg_initvariables(&BHarrayhead);

	//dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	//for (i=0; i < 256; i++)
	//{
	//	dg_pushbufferbyte(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 't');
	//}

	//dg_forthconstant(&BHarrayhead); 

	//pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_forthconstantnonameerror)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CONSTANT name too long error case - got wrong error \n");
	//}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error creating constant definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 8, (unsigned char*)"hi there");

	dg_forthcreate(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcreatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE error creating definition case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createvariabledefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE error creating definition case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dg_forthcreate(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE success case - got an error\n");
	}

	if (length + 9 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE success case - current input offset pointer not after delimiter after first word\n");
	}

	pdefinition = dg_getpdefinition(&BHarrayhead, 0);

	length = pdefinition->dataoffset;

	if (length != dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE success case - expected data offset to be length of data space buffer\n");
	}

	// not checking to see if I passed in  pointer to name correctly here

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CREATE success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdecimal()
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
#ifndef DGLU_NO_DIAPER
	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DECIMAL\n");

	// error setting base variable case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DECIMAL error setting state variable case - unable to initialize error stack\n");
		return;
	}

	dg_forthdecimal(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdecimalname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DECIMAL error setting state variable case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DECIMAL error setting state variable case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 88);

	dg_forthdecimal(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DECIMAL success case - error count not 0");
	}

	if (dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable) != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DECIMAL success case - state not execute\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DECIMAL success case - data  stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthdepth()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DEPTH\n");
#ifndef DGLU_NO_DIAPER
	// error getting data stack buffer length case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH error getting data stack buffer length case - unable to initialize error stack");
		return;
	}

	dg_forthdepth(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdepthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH error getting data stack buffer length case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH error getting data stack buffer length case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferlengthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH error getting data stack buffer length case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

    // error pushing to data stack case
	dg_initbuffers(&BHarrayhead);

    pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_DATASTACK_BUFFERID] );

      // data stack is of fixed size
    pBH->size = pBH->maxsize;
	pBH->growby = pBH->maxsize;
	pBH->nextunusedbyte = pBH->maxsize;

    dg_forthdepth(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdepthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH error pushing to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH error pushing to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH error pushing to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case empty data stack
	dg_initbuffers(&BHarrayhead);

	dg_forthdepth(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH empty data stack success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH empty data stack success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH empty data stack success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthdepth(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 1 * sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 5 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthdepth(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 5 * sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DEPTH 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthdrop ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DROP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthdrop(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdropname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);


	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP underflow case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthdrop(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdropname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9834);

	dg_forthdrop(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP success case - error count not 0 got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DROP success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthdup ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DUP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthdup(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP underflow case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthdup(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// grow error case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size =  pBH->maxsize;
	pBH->growby =  pBH->maxsize;
	pBH->nextunusedbyte =  pBH->maxsize;

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP push datastack error case - unable to initialize data stack");
		return;
	}

	 // could check where stack is corrupt, with just under 1 element

	dg_forthdup(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdupname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP push data stack error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 9834);

	dg_forthdup(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9834)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP success case - got wrong number on 2nd, got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 9834)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP success case - got wrong number on 4th, got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DUP success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
}


void testdg_forthelse()
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

	UINT64 ccbufid = 0;
	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

//	unsigned int length = 0;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing ELSE\n");
#ifndef DGLU_NO_DIAPER
	// error growing current compile buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 88);

	dg_forthelse(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthelsename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ELSE error growing current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_compilebranchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ELSE error growing current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_compilesegmentname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ELSE error growing current compile buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// if the grow was dg_successful, I cant think of a way of getting an error getting a pointer to the buffer

	// error doing then - will get error because data stack doesn't have ifoffset on it
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthelse(&BHarrayhead);  

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthelsename)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ELSE error doing then case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ELSE error doing then case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// don't know how to get error from pushing data stack because dg_forththen() checks for stack being there
	//  and stack is not being increased in size

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthif(&BHarrayhead);

	dg_forthelse(&BHarrayhead);  

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ELSE success case - got an error\n");
	}

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	pbuffer = dg_getpbuffer(&BHarrayhead, ccbufid, &plength);

	if ( *((UINT32*)(pbuffer + *plength - 9)) != 0x5 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ELSE success case - branch from if not calculated correctly\n");
	}

	if ( *(pbuffer + *plength - 5) != 0xE9 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ELSE success case - ELSE branch always opcode missing\n");
	}

	if ( *((UINT32*)(pbuffer + *plength - 4)) != 0x0 )
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! ELSE success case - unfinished branch always displacement not 0 \n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthemit ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing EMIT\n");
#ifndef DGLU_NO_DIAPER
	// error popping datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemit error popping data stack case - unable to initialize error stack");
		return;
	}

	dg_forthemit(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthemitname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemit error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemit error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemit error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)'G');

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nYou should see a G >>>");

	dg_forthemit(&BHarrayhead); 

	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthemit success case - got an error, got");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}

/*
void testdg_forthenvironmentquery ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ENVIRONMENT? - not tested here\n");

    // not tested here
}
*/

void testdg_forthevaluate ()
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

	unsigned char* testbuff = (unsigned char*)"3 7 *";
	UINT64 testbufflength = 5;
    
    UINT64 wordlist1;
    UINT64 word1;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing EVALUATE\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthevaluate(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthevaluatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE underflow case - unable to initialize data stack");
		return;
	}

	dg_forthevaluate(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthevaluatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // could test error creating new buffer

	// illegal address error - basically a crash test
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFFFFFFFF); // hopefully this is an illegal address
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);

	dg_forthevaluate(&BHarrayhead);

	//pError = dg_poperror(&BHarrayhead); // not sure what error the subroutine returns but we will get an error

	if (dg_geterrorcount(&BHarrayhead) == 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE illegal address case - didn't get an error %s\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

#endif 

	// success case
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead); // puts script engine into execute mode
    dg_inithlists (&BHarrayhead);
	//dg_initwordlists(&BHarrayhead);
    
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthstar),
		(unsigned char*)dg_forthstarname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, testbufflength);

	dg_forthevaluate(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE success case - error count not 0, got ");
        //pError = dg_poperror(&BHarrayhead);
        //dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE success case - expected result of calculation on the data stack, got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EVALUATE success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthexecute ()
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

	UINT64 i = 0;

	unsigned char cbuf[2];
    
    UINT64 wordlist1;
    UINT64 word1;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing EXECUTE\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack case
	dg_initbuffers(&BHarrayhead);

	dg_forthexecute(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthexecutename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error executing definition case
	//dg_initbuffers(&BHarrayhead);

	//dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2398493);

	//dg_forthexecute(&BHarrayhead);

	//if (dg_poperror(&BHarrayhead) != dg_forthexecuteexecutedefintionerror)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE executing definition case - got wrong error");
	//}

	//dg_freeallbuffers(&BHarrayhead);

	//dg_clearerrors(&BHarrayhead);
#endif
	// success case 0
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead); // puts script engine into execute mode
    
    dg_inithlists (&BHarrayhead);

	//dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthstore),
		(unsigned char*)dg_forthstorename);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
    

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2938);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(&i));

    // counted string for FIND
	cbuf[0] = 1; // number of characters in string
	cbuf[1] = '!'; // the string

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)cbuf);
	dg_forthfind(&BHarrayhead);
	dg_forthdrop(&BHarrayhead);

	dg_forthexecute(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE success case 0 - error count not 0\n");
	}

	if (i != 2938)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE success case 0 - number not stored\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE success case 0 - data stack not balanced after test\n");
		dg_forthdots(&BHarrayhead);
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 6
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthstar),
		(unsigned char*)dg_forthstarname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	cbuf[0] = 1;
	cbuf[1] = '*';

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)cbuf);
	dg_forthfind(&BHarrayhead);
	dg_forthdrop(&BHarrayhead);

	dg_forthexecute(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE success case 6 - error count not 0\n");
	}

	i = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (i != 21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE success case 6 - number not stored\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXECUTE success case 6 - data stack not balanced after test\n");
		dg_forthdots(&BHarrayhead);
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthexit ()
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

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing EXIT\n");

#ifndef DGLU_NO_DIAPER
	// error pushing to current compile buffer case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 3984);

	dg_forthexit(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthexitname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! EXIT error pushing to current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    } 

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthexit(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! EXIT success case - error count not 0\n");
	}

	if (dg_popbufferbyte(&BHarrayhead, DG_DATASPACE_BUFFERID) != 0xC3)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! EXIT success case - return not pushed to current compile buffer\n");
	}

	// for gcc on FreeBSD's wierdness on compiling comparisons of function returns and calculations
	/*
	length = length + 3;

	if (length != dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID))
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! EXIT success case - data space buffer length not balanced after test\n");
	}
	 */

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

void testdg_forthif()
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

	UINT64 ccbufid = 0;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing IF\n");
#ifndef DGLU_NO_DIAPER
	// testing dg_growbuffer case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	 //pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[i] );
	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[ccbufid] );
	
	pBH->size = pBH->nextunusedbyte;
	pBH->growby = pBH->nextunusedbyte;
	pBH->maxsize = pBH->nextunusedbyte;

	length = pBH->nextunusedbyte;

	dg_forthif(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthifname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF error growing buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_compilecallcorename)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF error growing buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    /*
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcompilebuffername)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF error growing buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF error growing buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    */

	if (length != pBH->nextunusedbyte)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF error growing buffer case - length changed\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// if grow buffer worked, I don't know how to get error from getting pointer

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	length = dg_getbufferlength(&BHarrayhead, ccbufid);

	dg_forthif(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF success case 1 - got an error \n");
	}

    // compile call core's length is shorter than if's old call core
	/*
    if (dg_getbufferlength(&BHarrayhead, ccbufid) != length + 24)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF success case 1 - expected buffer length to be 25\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, ccbufid, length) != 0xB80875FF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL IF success case 1 - code not compiled into buffer\n");
	}
	 */

    /*
	if (dg_getbufferlength(&BHarrayhead, ccbufid) != length + 25)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! IF success case 1 - expected buffer length to be 25\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, ccbufid, length) != 0x082574FF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL IF success case 1 - code not compiled into buffer\n");
	}
    */

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthfill ()
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

	unsigned char testbuff[20];

	UINT64 i = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing FILL\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthfill(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfillname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 90832);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL underflow case - unable to initialize data stack");
		return;
	}

	dg_forthfill(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfillname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// illegal address error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is an illegal address
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x38);

	dg_forthfill(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfillname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL illegal address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_fillwithbytename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL illegal address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case
	dg_initbuffers(&BHarrayhead);

	testint = 0;

	for (i = 0; i < 20; i++)
	{
		testbuff[i] = 0;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x38);

	dg_forthfill(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL success case - error count not 0\n");
	}

	if (testbuff[0] != 0x38)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL success case - character wasn't dg_forthstored at position 0\n");
	}

	if (testbuff[9] != 0x38)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL success case - character wasn't dg_forthstored at position 9\n");
	}

	if (testbuff[10] != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL success case - character at position 10 was changed\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FILL success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthfind ()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError;
	UINT64 testint = 0;

	Definitionheader* pdefinition;
	unsigned char* plstring;
	UINT64 lstringlength;

	unsigned char* pname1 = (unsigned char*)"\x002hi";
	unsigned char* pname2 = (unsigned char*)"\x001[";
	unsigned char* pname3 = (unsigned char*)"\x004OVER"; 
    
    UINT64 wordlist1;
    UINT64 word1;
    UINT64 word2;
    UINT64 word3;
	// NOTE: I tried to use \x003DUP but MS took \x003D to be '=', which is not what the documentation says it does
	
	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing FIND \n");

	// error doing COUNT case
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);

	dg_forthfind(&BHarrayhead); // error because data stack is empty

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfindname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND error doing count case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcountname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND error doing count case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error doing find
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 8, (unsigned char*)"hi there");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (unsigned char)' ');

	dg_forthword(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, 238);

	dg_forthfind(&BHarrayhead); // error because wordlist in search order does not exist

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfindname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND error doing find case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_finddefinsearchordername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND error doing find case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case word not found
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	//dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthstar),
		(unsigned char*)dg_forthstarname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)pname1);

	dg_forthfind(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word not found - error count not 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word not found - didn't get 0\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)pname1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word not found - didn't get pname back\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word not found - data  stack not empty after calculation\n");
		dg_forthdots(&BHarrayhead);
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case word found immediate
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	//dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypealwaysexecute),
		(UINT64)(&dg_forthleftbracket),
		(unsigned char*)dg_forthleftbracketname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    word2 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthover),
		(unsigned char*)dg_forthovername);

	dg_linkdefinition(&BHarrayhead, wordlist1, word2);
    
    word3 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthstar),
		(unsigned char*)dg_forthstarname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word3);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
    

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)pname2);

	dg_forthfind(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found immediate - error count not 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found immediate - didn't get 1 got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
    if (testint != word1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found immediate - didn't get [ execution token got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
	pdefinition = dg_getpdefinition(&BHarrayhead, testint);
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND succes case word found immediate - got error trying to use results of test\n");
	}
	else
	{
 
		// plstring = dg_getpbufferoffset(&BHarrayhead, pdefinition->namebufid, pdefinition->nameoffset);
		// lstringlength = pdefinition->namelength;
        
        plstring = dg_getshlistelementnom (
            &BHarrayhead,
            0, // hlistheaderid, wordlist 0
            testint, // elementid,
            &lstringlength); // pnamelength)

		if (plstring[0] != '[')
		{
			dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found immediate - got wrong definition\n");
		}

		if (lstringlength != 1)
		{
			dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found immediate - definition name length wrong, \n");
		}

		if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
		{
			dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found immediate - data  stack not empty after calculation\n");
			dg_forthdots(&BHarrayhead);
		}
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case word found
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypealwaysexecute),
		(UINT64)(&dg_forthleftbracket),
		(unsigned char*)dg_forthleftbracketname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    word2 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthover),
		(unsigned char*)dg_forthovername);

	dg_linkdefinition(&BHarrayhead, wordlist1, word2);
    
    word3 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthstar),
		(unsigned char*)dg_forthstarname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word3);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);

    

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)pname3);

	dg_forthfind(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found - error count not 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found - didn't get -1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    else
    {
        testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
        if (testint != word2)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found - found  wrong execution token expected ");
            dg_writestdoutuinttodec(&BHarrayhead, word2);
            dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
            dg_writestdoutuinttodec(&BHarrayhead, testint);
            dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        }
    
        pdefinition = dg_getpdefinition(&BHarrayhead, testint);

        //plstring = dg_getpbufferoffset(&BHarrayhead, pdefinition->namebufid, pdefinition->nameoffset);
        //lstringlength = pdefinition->namelength;
            //dg_getplstring(&BHarrayhead, nameoffsetbufferid, namestringbufferid, testint, &lstringlength);

        plstring = dg_getshlistelementnom (
            &BHarrayhead,
            0, // hlistheaderid, wordlist 0
            testint, // elementid,
            &lstringlength); // pnamelength)
            
        if (plstring[0] != 'O')
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found - got wrong definition\n");
        }

        if (lstringlength != 4)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found - definition name length wrong\n");
        }

        if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
        {
            dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FIND success case word found - data  stack not empty after calculation\n");
            dg_forthdots(&BHarrayhead);
        }
    }

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
}


void testdg_forthfmslashmod ()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing FM/MOD \n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthfmslashmod(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfmslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FM/MOD error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FM/MOD error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FM/MOD error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FM/MOD underflow case - unable to initialize data stack");
		return;
	}

	dg_forthfmslashmod(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthfmslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FM/MOD parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FM/MOD parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 22 FM/MOD 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 22 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 11)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 22 / 2 success case - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 22 / 2 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 22 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case -5 FM/MOD 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -5 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-3)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -5 / 2 success case - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -5 / 2 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -5 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case -7 FM/MOD -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -7 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -7 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -7 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -7 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case -1 FM/MOD -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -1 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -1 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 65535 FM/MOD -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65535 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65535)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65535 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65535 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65535 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 65536 FM/MOD -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65536 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65536)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65536 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65535 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD 65536 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case -10 FM/MOD 7 standard test case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 7);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! -10 FM/MOD 7 standard test case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! -10 FM/MOD 7 standard test case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 4)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! -10 FM/MOD 7 standard test case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! -10 FM/MOD 7 standard test case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 10 FM/MOD -7 standard test case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 10 FM/MOD -7 standard test case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL!10 FM/MOD -7 standard test case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-4)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 10 FM/MOD -7 standard test case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! 10 FM/MOD -7 standard test case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // +/0 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/0 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/0 case case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/0 case case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/0 case case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
    // -/0 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/0 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/0 case case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/0 case case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/0 case case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// +/+ overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0x8000000000000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/+ overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/+ overflow case case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/+ overflow case case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/+ overflow case case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
  
    // +/- overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0x8000000000000001);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/- overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/- overflow case case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/- overflow case case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD +/- overflow case case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // -/+ overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0x7FFFFFFFFFFFFFFF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/+ overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/+ overflow case case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/+ overflow case case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/+ overflow case case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
  
    // -/- overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0x8000000000000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthfmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/- overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/- overflow case case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/- overflow case case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! FM/MOD -/- overflow case case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // could test more near overflow and overflow cases with flooring
    //   but algorithm checks for overflow after flooring so those should work
}


void testdg_forthhere ()
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

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing HERE\n");
#ifndef DGLU_NO_DIAPER
	// error getting current variable buffer
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting current variable buffer case - unable to initialize buffers\n");
		return;
	}

	dg_forthhere(&BHarrayhead); // variable buffer not initialized... so...

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthherename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting current variable buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting current variable buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to current variable buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 30);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, 389);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting pointer to current variable buffer case - unable to initialize buffers\n");
		return;
	}

	dg_forthhere(&BHarrayhead); 
	
	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthherename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting pointer to current variable buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting pointer to current variable buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE getting pointer to current variable buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// error pushing to datastack
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size =  0;
	pBH->growby =  0;
	pBH->maxsize =  0;

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! pushing to datastack case - unable to initialize data stack\n");
		return;
	}

	dg_forthhere(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthherename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE pushing to datastack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE pushing to datastack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE pushing to datastack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE success case - unable to initialize data stack");
		return;
	}

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthhere(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE success case - got an error \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, 9834);

	*((UINT64*)testint) = 0xFFFEFDFC;

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE success case - data stack not empty\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID) != 0xFFFEFDFC)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HERE success case - got wrong address\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// could test case where current variable buffer is not dataspace buffer
}


void testdg_forthhold ()
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
	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing HOLD\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack buffer
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD popping data stack case - unable to initialize buffers\n");
		return;
	}

	dg_forthhold(&BHarrayhead); // data stack is empty

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthholdname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error inserting in pad case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_HOLD_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x38);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD error inserting in pad case - unable to initialize buffers\n");
		return;
	}

	dg_forthhold(&BHarrayhead); 
	
	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthholdname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD error inserting in pad case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthholdbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD error inserting in pad case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertinbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD error inserting in pad case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// if insert in pad worked, I don't know how to get an error putting to pad
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case - unable to initialize data stack");
		return;
	}

	dg_forthhold(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case - got an error \n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (pbuffer[0]  != 0x39)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case - character not inserted in buffer\n");
	}

	if (*plength != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case - pad buffer length not 1\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);

	// success case 2
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x37);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case 2 - unable to initialize data stack");
		return;
	}

	dg_forthhold(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case 2 - got an error \n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (pbuffer[0]  != 0x37)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case 2 - character not inserted in buffer\n");
	}

	if (pbuffer[1]  != 0x39)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case 2 - character not inserted in buffer\n");
	}

	if (*plength != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case 2 - pad buffer length not 1\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HOLD success case 2 - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthi ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing I\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I error getting pointer to rstack case - unable to initialize error stack");
		return;
	}

	dg_forthi(&BHarrayhead); // error because there is no r stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthiname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I error getting pointer to rstack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I error getting pointer to rstack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I underflow case - unable to initialize data stack");
		return;
	}

	dg_forthi(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthiname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_rstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// push datastack error case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
      // data stack is of fixed size
	pBH->size =  pBH->maxsize;
	pBH->growby = pBH->maxsize;
	pBH->nextunusedbyte = pBH->maxsize;

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I push datastack error case - unable to initialize data stack");
		return;
	}

	dg_forthi(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthiname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I push data stack error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	dg_forthi(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I success case - got wrong number on 2nd, got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I success case - data  stack not empty after test\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 2 * sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! I success case - rstack length changed\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}



void testdg_forthimmediate ()
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

	UINT64 definition = 0;
    UINT64 wordlist1;
	Definitionheader* pdefinition = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing IMMEDIATE\n");
#ifndef DGLU_NO_DIAPER
	// error getting current wordlist case
	dg_initbuffers(&BHarrayhead);

	dg_forthimmediate(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthimmediatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! IMMEDIATE error getting current wordlist case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcreatewordlistname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! IMMEDIATE error getting current wordlist case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! IMMEDIATE error getting current wordlist case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);
    
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);

	//dg_initwordlists(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, 0);

	definition = dg_createsubthreaddef(&BHarrayhead, (unsigned char*)"yo", 2);

	dg_linkdefinition(&BHarrayhead, wordlist1, definition);

	dg_forthimmediate(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! IMMEDIATE success case - error count not 0");
	}

	pdefinition = dg_getpdefinition(&BHarrayhead, definition);

	if (pdefinition->compileroutineoffset != (UINT64)(&dg_forthdocompiletypealwaysexecute))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! IMMEDIATE success case - compile routine not changed\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! IMMEDIATE success case - data stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthinvert()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing INVERT\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthinvert(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinvertname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthinvert(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinvertname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF INVERT 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthinvert(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT 0xFF000000000000FF success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x00FFFFFFFFFFFF00)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 INVERT
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthinvert(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 INVERT 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthinvert(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-6)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! INVERT 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthj ()
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
	UINT64 testint = 0;;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing J\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J error getting pointer to rstack case - unable to initialize error stack");
		return;
	}

	dg_forthj(&BHarrayhead); // error because there is no r stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthjname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J error getting pointer to rstack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J error getting pointer to rstack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J underflow case - unable to initialize data stack");
		return;
	}

	dg_forthj(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthjname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_rstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// push datastack error case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 2398);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size =  0;
	pBH->growby =  0;
	pBH->maxsize =  0;

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J push datastack error case - unable to initialize data stack");
		return;
	}

	dg_forthj(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthjname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J push data stack error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    
	// success case  
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 20);

	dg_forthj(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J success case - got wrong number on 2nd, got \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J success case - data  stack not empty after test\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 4 * sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! J success case - rstack length changed\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthleave ()
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

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing LEAVE\n");
#ifndef DGLU_NO_DIAPER
	// error growing current compile buffer case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 2983);

	dg_forthleave(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthleavename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LEAVE growing current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead); 

	if (pError != dg_compilebranchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LEAVE growing current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

	// error pushing to leave stack case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	dg_freebuffer(&BHarrayhead, DG_LEAVESTACK_BUFFERID);

	dg_forthleave(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthleavename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LEAVE pushing to leave stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthleavebufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LEAVE pushing to leave stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LEAVE pushing to leave stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthleave(&BHarrayhead);  

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LEAVE success case - got an error\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LEAVE success case - data stack not empty\n");
	}

	// for FreeBSD's wierdness in compiling comparisons of calculations and function returns
	length = length + 5;

	if (length != dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID))
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LEAVE success case - buffer not grown\n");
	}

	// for FreeBSD's wierdness in compiling comparisons of calculations and function returns
	length = length - 5;

	if (dg_getbufferbyte(&BHarrayhead, DG_DATASPACE_BUFFERID, length) != 0xE9)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LEAVE success case - first byte of compiled code missing\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, DG_DATASPACE_BUFFERID, length + 4) != 0x0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LEAVE success case - last byte of compiled code missing\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_LEAVESTACK_BUFFERID) != length + 5)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LEAVE success case - leave branch offset missing from leave stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_LEAVESTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LEAVE success case - leave stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthliteral ()
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
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 x = 0;
	UINT64 mystartoffset = 0;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing LITERAL\n");
#ifndef DGLU_NO_DIAPER
	// error getting current compile buffer
	dg_initbuffers(&BHarrayhead);

	dg_forthliteral(&BHarrayhead);  // variables not initialized

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthliteralname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL error getting current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL error getting current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL error getting current compile buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error popping data stack case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthliteral(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthliteralname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - could not get current compile buffer\n");
		return;
	}
	
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to push a number to the data stack
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - could not compile init locals\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1165239486756633);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - could not push test number to data stack\n");
		return;
	}
	
	
	dg_forthliteral(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL!LITERAL success case - could not do dg_forthliteral\n");
		return;
	}
	
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - dg_forthliteral did not consume data stack parameter\n");
		return;
	}
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0x1165239486756633)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LITERAL success case - top number on data stack after calling compiled LITERAL incorrect\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
}


void testdg_checkloopdone ()
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

	UINT64 flag = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_checkloopdone\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to rstack case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_RSTACK_BUFFERID);

	flag = dg_checkloopdone(&BHarrayhead); // error because there is no r stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_checkloopdonename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone error getting pointer to rstack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone error getting pointer to rstack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone error getting pointer to rstack case - expected FORTH_TRUE\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x55667788);

	flag = dg_checkloopdone(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_checkloopdonename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_rstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone parameters missing case - expected FORTH_TRUE\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case not done
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 8);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	flag = dg_checkloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done - error count not 0");
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done - rstack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case done
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 9);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	flag = dg_checkloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case done - error count not 0");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case done - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone checkloopdone dg_success case done - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone checkloopdone dg_success case done - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone checkloopdone dg_success case done - rstack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case not done2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 10);

	flag = dg_checkloopdone(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done2 - error count not 0");
	}

	if (flag != FORTH_FALSE) // this is what the standard says happens
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done2 - expected FORTH_FALSE\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done2 - got wrong limit \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done2 - got wrong index \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_checkloopdone success case not done2 - rstack not empty after calculation\n");
	}
 
    dg_clearerrors(&BHarrayhead);   

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthloop ()
{
	Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
	const char* pError = NULL;
	
	UINT64 mycurrentcompilebuffer = 0;
	UINT64 mystartoffset = 0;
	UINT64 x = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing LOOP\n");
#ifndef DGLU_NO_DIAPER	
	
	// error getting pointer to leave buffer case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	dg_freebuffer(&BHarrayhead, DG_LEAVESTACK_BUFFERID);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	
	dg_forthloop(&BHarrayhead);
	
	pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forthloopname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP error getting pointer to leave buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
    pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forthleavebufferidname)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP error getting pointer to leave buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
    pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP error getting pointer to leave buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
	
	// error resolving leave case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	
	dg_pushbufferuint64(&BHarrayhead, DG_LEAVESTACK_BUFFERID, 23894);
	
	dg_forthloop(&BHarrayhead);
	
	pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forthloopname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LOOP error resolving leave case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
    pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LOOP error resolving leave case case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	
	// success case 
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compile function to do DO 1+ LOOP
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not compile init locals\n");
		return;
	}
	
	dg_forthdo(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not do dg_forthdo\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)&dg_forthoneplus);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not compile call to dg_forthoneplus\n");
		return;
	}
	
	dg_forthloop(&BHarrayhead); 
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case - error count not 0");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_LEAVESTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case - data  stack not empty after calculation\n");
	}		
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 16);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could push test counter to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not push loop terminator value to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - could not loop start value to data stack\n");
		return;
	}
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - got error executing compiled test routine\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 26)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case - test counter output from compiled function wrong value, probably due to incorrect loop operation, expected 26, got ");
		dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
	
	
	// success case3 doing a leave 
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not get current compile buffer's length\n");
		return;
	}
	
	// compile function to do DO 1+ DUP 5 = IF LEAVE THEN 1 +LOOP
	//  depends on other functions working so +LOOP test should go at end
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not compile init locals\n");
		return;
	}
	
	dg_forthdo(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not do dg_forthdo\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)(&dg_forthoneplus));
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not do compile call to dg_forthoneplus\n");
		return;
	}
	
	dg_forthleave(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not do dg_forthleave\n");
		return;
	}
	
	dg_forthloop(&BHarrayhead);  
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case3 doing a leave - error count not 0");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case3 doing a leave - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_LEAVESTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case3 doing a leave - data  stack not empty after calculation\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LOOP success case3 doing a leave - data  stack not empty after calculation\n");
	}		
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 16);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not push test counter to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not push loop terminator value to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - could not push loop start value to data stack\n");
		return;
	}
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - got error calling compiled function\n");
		return;
	}
	
	// should have just done 1 loop
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 17)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing LOOP success case3 doing a leave - test counter incorrect after calling compiled function\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
	
	// need to test more leave cases
}


void testdg_forthlshift()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing LSHIFT\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthlshift(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlshiftname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LSHIFT error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LSHIFT error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LSHIFT error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthlshift(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlshiftname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LSHIFT parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! LSHIFT parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 0xFF0000FF LSHIFT 4
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthlshift(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT 0xFF000000000000FF LSHIFT 4 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xF000000000000FF0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT 0xFF000000000000FF LSHIFT 4 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT 0xFF000000000000FF LSHIFT 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 LSHIFT 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthlshift(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT -1 LSHIFT 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT -1 LSHIFT 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT -1 LSHIFT 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 LSHIFT 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthlshift(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT 5 LSHIFT 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 160)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT 5 LSHIFT 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! LSHIFT 5 LSHIFT 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthmstar()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing M*\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthmstar(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M* error getting pointer to data stack case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M* error getting pointer to data stack case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M* error getting pointer to data stack case - got wrong error 2 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthmstar(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M* underflow case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M* underflow case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

#endif    

    

	// success case 22 * s
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 22 * 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 22 * 2 success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 44)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 22 * 2 success case lo - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 22 * 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -2 * -5 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);


	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* -2 * -5 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* -2 * -5 success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 10)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* -2 * -5 success case lo - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* -2 * -5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 3 * -7 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);

	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 3 * -7 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 3 * -7 success case hi - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-21)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 3 * -7 success case lo - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 3 * -7 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 * -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 1 * -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 1 * -1 / -1 success case hi - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 1 * -1 / -1 success case lo - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 1 * -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -65535 * 1 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65535 * -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65535 * -1 success case hi- got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65535)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65535 * -1 success case lo- got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65535 * -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65536 * -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65536 * -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65536 * -1 success case hi - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65536)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65536 * -1 success case lo - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 65536 * -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 * 0x100000000
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);

	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * 0x100000000  / 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1) 
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * 0x100000000  / 1 success case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0) 
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * 0x100000000  / 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * 0x100000000  / 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 * -0x100000000
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-0x100000000);

	dg_forthmstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * -0x100000000 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * -0x100000000 / -1 success case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)  
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * -0x100000000 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! M* 0x100000000 * -0x100000000 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthmax()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing MAX\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthmax(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmaxname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthmax(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmaxname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 65536 MAX 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthmax(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX 65536 MAX 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65536)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX 65536 MAX 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX 65536 MAX 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 MAX 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthmax(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX -1 MAX 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX -1 MAX 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX -1 MAX 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 MAX 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthmax(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX 5 MAX 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX 5 MAX 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MAX 5 MAX 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthmin()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing MIN\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthmin(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthminname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthmin(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthminname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 65536 MIN 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthmin(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN 65536 MIN 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 20)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN 65536 MIN 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN 65536 MIN 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 MIN 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthmin(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN -1 MIN 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN -1 MIN 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN -1 MIN 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 MIN 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthmin(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN 5 MIN 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN 5 MIN 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MIN 5 MIN 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthmod()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing MOD \n");


	// success case 22 MOD 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD 22 MOD 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD  22 MOD 2 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD 22 MOD 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -5 MOD 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -5 MOD 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -5 MOD 2 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -5 MOD 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// _success case -7 MOD -4
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-4);

	dg_forthmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -7 MOD -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-3)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -7 MOD -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -7 MOD -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 MOD -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -1 MOD -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -1 MOD -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -1 MOD -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65535 MOD -2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);

	dg_forthmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD 65535 MOD -2 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD 65535 MOD -2 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD 65535 MOD -2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -65536 MOD 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -65536 MOD 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -65536 MOD 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! MOD -65536 MOD 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    	
}


void testdg_forthmove ()
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

	unsigned char testbuff[20];

	UINT64 i = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing MOVE\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthmove(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmovename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 90832);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE underflow case - unable to initialize data stack");
		return;
	}

	dg_forthmove(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmovename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// illegal address error
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is an illegal address
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);

	dg_forthmove(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmovename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE illegal address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_movebytesname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE illegal address case - got wrong error 1 below, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE illegal address case - got wrong error 2 below, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// illegal address error dec
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-10); // hopefully this is an illegal address
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);

	dg_forthmove(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthmovename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE illegal address case dec- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_movebytesname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE illegal address case dec- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthminusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE illegal address case dec- got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case inc
	dg_initbuffers(&BHarrayhead);

	testint = 0;

	for (i = 0; i < 20; i++)
	{
		testbuff[i] = (unsigned char)i;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 1));
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 3));
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthmove(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case - error count not 0\n");
	}

	if (testbuff[3] != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case - wrong character dg_forthstored at position 3\n");
	}

	if (testbuff[7] != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case - wrong dg_forthstored at position 7\n");
	}

	if (testbuff[8] != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case - character at position 8 was changed\n");
	}

	if (testbuff[2] != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case - character at position 0 was changed\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case dec
	dg_initbuffers(&BHarrayhead);

	testint = 0;

	for (i = 0; i < 20; i++)
	{
		testbuff[i] = (unsigned char)i;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 3));
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 1));
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthmove(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case dec - error count not 0\n");
	}

	if (testbuff[1] != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case dec - wrong character dg_forthstored at position 3\n");
	}

	if (testbuff[5] != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case dec - wrong dg_forthstored at position 7\n");
	}

	if (testbuff[6] != 6)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case dec - character at position 8 was changed\n");
	}

	if (testbuff[0] != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case dec - character at position 0 was changed\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! MOVE success case dec - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthslash()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing /\n");

	// success case 22 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / 22 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 11)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /  22 / 2 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / 22 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -5 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -5 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -5 / 2 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -5 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -7 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -7 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -7 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -7 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -1 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65535 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / 65535 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65535)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / 65535 / -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / 65535 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -65536 / 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthslash(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -65536 / 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65536)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -65536 / 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! / -65536 / 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthslashmod ()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing /MOD \n");

	// success case 22 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 22 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 11)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 22 / 2 success case - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 22 / 2 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 22 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -5 / 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -5 / 2 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -5 / 2 success case - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -5 / 2 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -5 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -7 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -7 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -7 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -7 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -7 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -1 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -1 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65535 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65535 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65535)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65535 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65535 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65535 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65536 / -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65536 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65536)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65536 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65535 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! /MOD 65536 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// check divide by 0 case
	// check 4 test cases from standard for symmetric divide
}


void testdg_forthnegate()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing NEGATE\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthnegate(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnegatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthnegate(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnegatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 0xFF0000FF NEGATE 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthnegate(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE 0xFF000000000000FF success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x00FFFFFFFFFFFF01)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case -1 NEGATE
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthnegate(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 5 NEGATE 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthnegate(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-5 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NEGATE 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
}


void testdg_forthor()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing OR\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthor(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthorname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthor(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthorname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 0xFF0000FF OR 0x03C003C0
    dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF00FF0000FF00FF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x03C003C003C003C0);

	dg_forthor(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR 0xFF00FF0000FF00FF OR 0x03C003C003C003C0 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFFC0FFC003FF03FF)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR 0xFF00FF0000FF00FF OR 0x03C003C003C003C0 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR 0xFF00FF0000FF00FF OR 0x03C003C003C003C0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 OR 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthor(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR -1 OR 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR -1 OR 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR -1 OR 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 OR 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthor(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR 5 OR 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR 5 OR 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR 5 OR 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}



void testdg_forthover ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing OVER\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to the data stack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthover(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthovername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthover(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthovername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing data stack
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x11223344);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = 2*sizeof(UINT64);
	pBH->growby = 2*sizeof(UINT64);
	pBH->maxsize = 2*sizeof(UINT64);

	dg_forthover(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthovername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER push data stack error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x12345678);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x9ABCDEF0);

	dg_forthover(&BHarrayhead); // error because there is no data stack yet

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x12345678)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER success case - wrong number on top of stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x9ABCDEF0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER success case - wrong number 2nd top of stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x12345678)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER success case - wrong number on top of stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OVER success  case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthpostpone ()
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

	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	UINT64 length = 0;
    
    UINT64 wordlist1;
    UINT64 word1;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing POSTPONE\n");
#ifndef DGLU_NO_DIAPER
	// error doing ' case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthpostpone(&BHarrayhead); // terminal input buffer is empty - no name error from tick

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpostponename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE error doing ' case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE error doing ' case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// can't get error popping definition token if ' worked

	// word not found error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	//dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthstar),
		(unsigned char*)dg_forthstarname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
    

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 8, (unsigned char*)"hi there");

	dg_forthpostpone(&BHarrayhead); // hi not in wordlists

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpostponename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE word not found case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_wordnotfoundinsearchordererror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE word not found case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// if i was able to get the definition, dg_getpdefinition should work... 	

	// success case [
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);
	
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	dg_forthrightbracket(&BHarrayhead);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 7, (unsigned char*)"[ there");

    dg_inithlists (&BHarrayhead);
    
	//dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypealwaysexecute),
		(UINT64)(&dg_forthleftbracket),
		(unsigned char*)dg_forthleftbracketname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
    

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthpostpone(&BHarrayhead); // should have compiled a call to dg_forthexecute

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE success case [ - error count not 0\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	//if (*plength != length + 14)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE success case - expected 14 compiled bytes\n");
	//}

	//if (*((UINT64*)(pbuffer + length + 5)) != (UINT64)&dg_forthleftbracket)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE success case - expected compilation of dg_forthrightbracket address\n"); 
	//}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR -1 OR 1 success case [ - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case DUP
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);
	
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	dg_forthrightbracket(&BHarrayhead);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 9, (unsigned char*)"DUP there");

    dg_inithlists (&BHarrayhead);
    
	//dg_initwordlists(&BHarrayhead);
    
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
		(UINT64)(&dg_forthdocompiletypesubroutine),
		(UINT64)(&dg_forthdup),
		(unsigned char*)dg_forthdupname);

	dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
    

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthpostpone(&BHarrayhead); // should have compiled a call to dg_forthleftbracket

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE success case DUP - error count not 0\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	//if (*plength != length + 14)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE success case DUP - expected 14 compiled bytes\n");
	//}

	//if (*((UINT64*)(pbuffer + length + 5)) != (UINT64)&dg_forthdup)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE success case DUP - expected compilation of dg_forthrightbracket address\n"); 
	//}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! POSTPONE success case DUP - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthrfrom ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing R>\n");
#ifndef DGLU_NO_DIAPER
	// error popping rstack case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthrfrom(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrfromname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> underflow case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing data stack
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x11223344);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = 0*sizeof(UINT64);
	pBH->growby = 0*sizeof(UINT64);
	pBH->maxsize = 0*sizeof(UINT64);

	dg_forthrfrom(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrfromname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> push data stack error case - got wrong error on top, got ");
	    dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> push data stack error case - got wrong error 1 below top, got ");
	    dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> push data stack error case - got wrong error 2 below top, got ");
	    dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x123456789abcdef0);

	dg_forthrfrom(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x123456789abcdef0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> success case - wrong number on top of stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> success  case - data stack not empty after test\n");
	}

		if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R> success  case - rstack not empty after test\n");
	}


	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthrfetch()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing R@\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to rstack case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_RSTACK_BUFFERID);

	dg_forthrfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ error getting pointer to rstack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ error getting pointer to rstack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthrfetch(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_rstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// push datastack error error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 00);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthrfetch(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrfetchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ push data stack error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x2299553399447711);

	dg_forthrfetch(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ success case - got an error\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x2299553399447711)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ success case - data stack didn't get right number\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

	if (testint != 0x2299553399447711)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ success case - rstack missing number\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ success case - data stack length not 0 after test\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! R@ success case - rstack length not 0 after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthrecurse ()
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
	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing RECURSE\n");
#ifndef DGLU_NO_DIAPER
    
	// underflow case 
	dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);

	dg_forthrecurse(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrecursename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RECURSE no definitions declared case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_underflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RECURSE no definitions declared case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// can't access state variable case
      // won't be able to access hlists first so...
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_newword(&BHarrayhead, 
		DG_CORE_BUFFERID, 
		(UINT64)&dg_forthdocompiletypesubroutine, 
		DG_CORE_BUFFERID, 
		(UINT64)&dg_forthdup,
		DG_CORE_BUFFERID,
		(UINT64)"DUPPY", 
		5);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, DG_DATASPACE_BUFFERID);

	length = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_forthrecurse(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RECURSE success case - got an error\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthrepeat()
{
    Bufferhandle BHarrayhead;
	
	dg_initpbharrayhead(&BHarrayhead);
	
	const char* pError = NULL;
	
	UINT64 mycurrentcompilebuffer;
	UINT64 mystartoffset;
	UINT64 x;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing REPEAT\n");
#ifndef DGLU_NO_DIAPER	
	
	// error popping data stack case 
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	dg_forthrepeat(&BHarrayhead); 
	
	pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forthrepeatname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! REPEAT error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
    pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! REPEAT error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
	
	// compile THEN error
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 00);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 00);
	
	dg_forthrepeat(&BHarrayhead); // branch offset too close to beginning of buffer among other  things
	
	pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forthrepeatname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! REPEAT compile THEN error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
    pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! REPEAT compile THEN error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
#endif	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compile function to do BEGIN DUP 0= 0= WHILE 1- REPEAT
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not compile init locals\n");
		return;
	}
	
	dg_forthbegin(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not do dg_forthbegin\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)&dg_forthdup);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not compile call to dg_forthdup\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)&dg_forthzeroequals);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not compile call to dg_forthzeroequals\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)&dg_forthzeroequals);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not compile call to dg_forthzeroequals\n");
		return;
	}
	
	dg_forthwhile(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not do dg_forthwhile\n");
		return;
	}
	
	dg_compilecallcore(&BHarrayhead, (UINT64)&dg_forthoneminus);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not compile call to dg_forthoneminus\n");
		return;
	}
	
	dg_forthrepeat(&BHarrayhead); 
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! REPEAT success case - doing repeat error count not 0\n");
		pError = dg_poperror(&BHarrayhead);
		dg_forthdoterrors(&BHarrayhead);
		//dg_printzerostring(&BHarrayhead,  (unsigned char*)"got error ");
		//dg_printzerostring(&BHarrayhead,  (unsigned char*)pError);
		//dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
		return;
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! REPEAT success case - data  stack not empty after calculation\n");
	}
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - could not push loop terminator value to data stack\n");
		return;
	}
	
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - got error executing compiled test routine\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing REPEAT success case - test counter output from compiled function wrong value, expected 0, got ");
		dg_writestdoutuinttodec(&BHarrayhead, x);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    	
}


void testdg_forthrot ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ROT\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to the data stack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthrot(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrotname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthrot(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrotname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1234567811223344);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x9ABCDEF556677880);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x2288446613579864);

	dg_forthrot(&BHarrayhead); // error because there is no data stack yet

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x1234567811223344)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT success case - wrong number on top of stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x2288446613579864)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT success case - wrong number 2nd top of stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x9ABCDEF556677880)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT success case - wrong number 3rd top of stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROT success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}



void testdg_forthrshift()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing RSHIFT\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthrshift(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrshiftname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RSHIFT error getting pointer to data stack case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RSHIFT error getting pointer to data stack case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RSHIFT error getting pointer to data stack case - got wrong error 2 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RSHIFT underflow case - unable to initialize data stack\n");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthrshift(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrshiftname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RSHIFT parameters missing case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! RSHIFT parameters missing case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 0xFF000000000000FF LSHIFT 4
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forthrshift(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT 0xFF000000000000FF RSHIFT 4 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x0FF000000000000F)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT 0xFF000000000000FF RSHIFT 4 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT 0xFF000000000000FF RSHIFT 4 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case -1 RSHIFT 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthrshift(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT -1 RSHIFT 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT -1 RSHIFT 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT -1 RSHIFT 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 5 RSHIFT 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthrshift(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT 5 RSHIFT 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT 5 RSHIFT 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! RSHIFT 5 RSHIFT 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
   
}


void testdg_forthstod ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing S>D\n");
#ifndef DGLU_NO_DIAPER
	// error popping datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D popping data stack case - unable to initialize error stack");
		return;
	}

	dg_forthstod(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error pushing data stack case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = sizeof(UINT64);
	pBH->growby = sizeof(UINT64);
	pBH->maxsize = sizeof(UINT64);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D push error case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthstod(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D push error  case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D push error  case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D push error  case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthstod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D 0 success case - error count not 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D 0 success case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D 0 success case - got wrong answer2 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case not 0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x8000000000000000);

	dg_forthstod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D not 0 success case - error count not 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D not 0 success case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D not 0 success case - got wrong answer2 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! S>D not 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthsign ()
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

	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;


	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing SIGN\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack buffer
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN popping data stack case - unable to initialize buffers\n");
		return;
	}

	dg_forthsign(&BHarrayhead); // data stack is empty

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// error inserting in pad case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_HOLD_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-4);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN error inserting in pad case - unable to initialize buffers\n");
		return;
	}

	dg_forthsign(&BHarrayhead); 
	
	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsignname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN error inserting in pad case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthholdbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN error inserting in pad case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertinbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN error inserting in pad case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// if insert in pad worked, I don't know how to get an error putting to pad

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x39);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case - unable to initialize data stack");
		return;
	}

	dg_forthsign(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case - got an error \n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (*plength != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case - pad buffer length not 0\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);

	// success case 2
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case 2 - unable to initialize data stack");
		return;
	}

	dg_forthsign(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case 2 - got an error \n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_HOLD_BUFFERID, &plength);

	if (pbuffer[0]  != '-')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case 2 - character not inserted in buffer\n");
	}

	if (*plength != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case 2 - pad buffer length not 1\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SIGN success case 2 - data stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthsmslashrem ()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing SM/REM \n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthsmslashrem(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsmslashremname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SM/REM error getting pointer to data stack case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SM/REM error getting pointer to data stack case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SM/REM error getting pointer to data stack case - got wrong error 2 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthsmslashrem(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsmslashremname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SM/REM parameters missing case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SM/REM parameters missing case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 22 SM/REM 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 22 / 2 success case - error count not 0\n");
	}

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
	if (testint != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SM/REM 22 / 2 success case - got wrong answer, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 22 / 2 success case - got wrong remainder, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 22 / 2 success case - data  stack not empty after calculation.\n");
    }

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -5 SM/REM 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -5 / 2 success case - error count not 0\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -5 / 2 success case - got wrong answer, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -5 / 2 success case - got wrong remainder, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, testint);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -5 / 2 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -7 SM/REM -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -7 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 7)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -7 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -7 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -7 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 SM/REM -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -1 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -1 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -1 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -1 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65535 SM/REM -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65535);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65535 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65535)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65535 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65535 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65535 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 65536 SM/REM -1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65536 / -1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-65536)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65536 / -1 success case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65535 / -1 success case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM 65536 / -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // +/0 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/0 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/0 case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/0 case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/0 case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	 // -/0 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/0 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/0 case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/0 case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/0 case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // +/+ overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x8000000000000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)1);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/+ overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/+ overflow case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/+ overflow case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/+ overflow case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // +/- overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x8000000000000001);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/- overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/- overflow case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/- overflow case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM +/- overflow case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // -/+ overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x7FFFFFFFFFFFFFFF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)1);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/+ overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/+ overflow case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/+ overflow case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM -/+ overflow case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    


    // success 10/7 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)7);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/7 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/7 case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 3)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/7 case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/7 case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    
    // success -10/7 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)7);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/7 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/7 case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-3)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/7 case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/7 case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // success 10/-7 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/-7 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/-7 case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)3)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/-7 case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success 10/-7 case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // success -10/-7 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-10);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/-7 case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/-7 case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-3)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/-7 case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success -10/-7 case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    
    // success +/+ near overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0xFFFFFFFFFFFFFFFF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)2);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/+ near overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)0x7FFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/+ near overflow case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/+ near overflow case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/+ near overflow case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    
    // success +/- near overflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);

	dg_forthsmslashrem(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/- near overflow case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)0x8000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/- near overflow case - got wrong answer \n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/- near overflow case - got wrong remainder\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! SM/REM success +/- near overflow case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthsource()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing SOURCE\n");
#ifndef DGLU_NO_DIAPER
	// error getting current interpret buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE error getting current interpret buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthsource(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsourcename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE error getting current interpret buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentinputbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE error getting current interpret buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE error getting current interpret buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to current interpret buffer error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_freebuffer(&BHarrayhead, DG_TERMINALINPUT_BUFFERID);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE getting pointer to current interpret buffer error case - unable to initialize data stack");
		return;
	}

	dg_forthsource(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsourcename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE getting pointer to current interpret buffer error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentinputbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE getting pointer to current interpret buffer error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE getting pointer to current interpret buffer error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// push pointer error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = 0;
	pBH->growby = 0;
	pBH->maxsize = 0;

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push pointer error case - unable to initialize data stack");
		return;
	}

	dg_forthsource(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsourcename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push pointer error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push pointer error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push pointer error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// push length error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
	
	pBH->size = sizeof(UINT64);
	pBH->growby = sizeof(UINT64);
	pBH->maxsize = sizeof(UINT64);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push length error case - unable to initialize data stack");
		return;
	}

	dg_forthsource(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthsourcename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push length error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push length error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE push length error case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbufferuint64(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 383498);

	dg_forthsource(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE success case - error count not 0");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, &plength);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != *plength)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE success case - got wrong length \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)pbuffer)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE success case - got wrong address \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SOURCE success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthspace ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing SPACE\n");

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nYou should see a space >>>");

	dg_forthspace(&BHarrayhead); 

	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthspace success case - got an error");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthspaces ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing SPACES\n");
#ifndef DGLU_NO_DIAPER
	// error popping data stack case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthspaces(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthspacesname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SPACES error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SPACES error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SPACES error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nYou should see 5 spaces >>>");
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthspaces(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
}


void testdg_forthstate ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing STATE\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE error getting pointer to base variable case - unable to initialize error stack");
		return;
	}

	dg_forthstate(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE error getting pointer to base variable case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffersegmentname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE error getting pointer to base variable case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// push data stack error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE push data stack error case - unable to initialize data stack");
		return;
	}

	dg_forthstate(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthstate(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != ((UINT64)dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength)) + statevariable)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! STATE success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);  
}


void testdg_forthswap()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing SWAP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to the data stack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstore error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthswap(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthswapname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SWAP error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SWAP error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SWAP error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthswap(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthswapname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SWAP underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SWAP underflow case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x12345678);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x9ABCDEF0);

	dg_forthswap(&BHarrayhead); // error because there is no data stack yet

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x12345678)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success case - wrong number on top of stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x9ABCDEF0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success case - wrong number 2nd top of stack\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forththen()
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

	UINT64 ccbufid = 0;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing THEN\n");
#ifndef DGLU_NO_DIAPER
	// error getting current compile buffer case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forththen(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error getting current compile buffer id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcompilebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error getting current compile buffer id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error getting current compile buffer id case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting current compile buffer length case - have to set current compile buffer to another buffer to test this
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 88);

	dg_forththen(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error getting current compile buffer length case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentcompilebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error getting current compile buffer length case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferlengthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error getting current compile buffer length case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error popping old offset from the data stack
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forththen(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error popping old offset from the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error popping old offset from the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error popping old offset from the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// branch resolution offset off the end of the buffer case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	// dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, dg_getbufferlength(&BHarrayhead, ccbufid) + 1);

    dg_pushdatastack(&BHarrayhead, dg_getbufferlength(&BHarrayhead, ccbufid) + 1);

	dg_forththen(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error branch resolution offset is off the end of the buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_resolvecompiledbranchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error branch resolution offset is off the end of the buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// branch offset too close to the beginning of the buffer case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, 4);

	// dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	dg_forththen(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error branch resolution offset is too close to the beginning of the buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_resolvecompiledbranchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN error branch resolution offset is too close to the beginning of the buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// opcode missing case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	dg_pushbufferbyte(&BHarrayhead, ccbufid, 22);
	dg_pushbufferuint64(&BHarrayhead, ccbufid, 0);
    
    dg_pushdatastack(&BHarrayhead, dg_getbufferlength(&BHarrayhead, ccbufid));
	
	// dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, dg_getbufferlength(&BHarrayhead, ccbufid));

	dg_forththen(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN opcode missing at buffer offset case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_resolvecompiledbranchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN opcode missing at buffer offset case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// default branch offset not 0 case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, 4);

	// dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	dg_pushbufferbyte(&BHarrayhead, ccbufid, 0x80);
	dg_pushbufferuint32(&BHarrayhead, ccbufid, 1);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, dg_getbufferlength(&BHarrayhead, ccbufid));

	dg_forththen(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forththenname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN displacement at offset not 0 case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_resolvecompiledbranchname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN displacement at offset not 0 case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_branchalreadyresolvederror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! THEN displacement at offset not 0 case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case w/ 0 displacement
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	// dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushdatastack(&BHarrayhead, 4);

	ccbufid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

	dg_pushbufferbyte(&BHarrayhead, ccbufid, 0x80);
	dg_pushbufferuint32(&BHarrayhead, ccbufid, 0);

	length = dg_getbufferlength(
        &BHarrayhead,
        ccbufid);
	
	dg_pushbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID,
        length);

	dg_forththen(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ 0 displacement - got an error\n");
	}

	if (dg_getbufferlength(&BHarrayhead, ccbufid) != length)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ 0 displacement - length of buffer changed\n");
	}

	if (dg_getbufferuint32(&BHarrayhead, ccbufid, length - 4) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ 0 displacement - displacement not 0\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, ccbufid, length - 5) != 0x80)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ 0 displacement - opcode changed\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case w/ >0 displacement
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);

	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);

	dg_pushbufferbyte(&BHarrayhead, ccbufid, 0x80);
	dg_pushbufferuint32(&BHarrayhead, ccbufid, 0);
	dg_pushbufferuint32(&BHarrayhead, ccbufid, 0xffeeddcc);

	length = dg_getbufferlength(&BHarrayhead, ccbufid);
	
	// dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, length - 4);
    dg_pushdatastack(&BHarrayhead, length - 4);

	dg_forththen(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ > 0 displacement - got an error\n");
	}

	if (dg_getbufferlength(&BHarrayhead, ccbufid) != length)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ > 0 displacement - length of buffer changed\n");
	}

	if (dg_getbufferuint32(&BHarrayhead, ccbufid, length - 8) != 4)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ > 0 displacement - displacement not 4\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, ccbufid, length - 9) != 0x80)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ > 0 displacement - opcode changed\n");
	}

	if (dg_getbufferuint32(&BHarrayhead, ccbufid, length - 4) != 0xffeeddcc)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! THEN success case w/ > 0 displacement - stuff after branch changed\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthtype ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing TYPE\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initbuffers(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

	dg_forthtype(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtypename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE underflow case - unable to initialize data stack");
		return;
	}

	dg_forthtype(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthtypename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// bad address case
    // v1.5 does not trap operating system exceptions
#endif
	// success case 65536 U< 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)"hi there");
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 8);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"You should see 'hi there' >>>");
	dg_forthtype(&BHarrayhead);
	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE success case - error count not 0");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
 
    
    // success length 0 case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)"hi there");
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthtype(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE success length 0 case - error count not 0");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! TYPE success length 0 case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthudot ()
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


	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing U.\n");

	// success case 1
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nYou should see '342 ' >>>");
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 342);

	dg_forthudot(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");

	// success case 2
	dg_initbuffers(&BHarrayhead);
	dg_initvariables(&BHarrayhead);

	dg_forthhex(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\nYou should see 'FFFFFFFFFFFFFFFF ' >>>");
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthudot(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
}


void testdg_forthulessthan()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing U<\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthulessthan(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthulessthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthulessthan(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthulessthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 U< 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthulessthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< 65536 U< 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< 65536 U< 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< 65536 U< 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 U< 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthulessthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< -1 U< 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< -1 U< 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< -1 U< 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 U< 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthulessthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< 5 U< 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< 5 U< 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U< 5 U< 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}



void testdg_forthumstar()
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

	const char* pError = NULL;
//	unsigned int testint = 0;

//	unsigned int bufid = 0;
//	unsigned int* plength = NULL;
//	unsigned char* pbuffer = NULL;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing UM* \n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM*  error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthumstar(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthumstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM*  error getting pointer to data stack case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM*  error getting pointer to data stack case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM*  error getting pointer to data stack case - got wrong error 2 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM*  underflow case - unable to initialize data stack\n");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthumstar(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthumstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM*  address and maybe data missing case - got wrong error on top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM*  address and maybe data missing case - got wrong error 1 below top, got ");
		dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 100 UM* 22
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);

	dg_forthumstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM*  22 UM* 100 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM*  22 UM* 100 success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 2200)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM*  22 UM* 100 success case lo - got wrong answer\n");
	}


	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM*  22 UM* 100 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x100000000 UM* 0x100000000
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x100000000);

	dg_forthumstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM* 0x100000000 UM* 0x100000000 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM* 0x100000000 UM* 0x100000000 success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM* 0x100000000 UM* 0x100000000 success case lo - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM* 0x100000000 UM* 0x100000000 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    


}


void testdg_forthumslashmod ()
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

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing UM/MOD \n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthumslashmod(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthumslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM/MOD  error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM/MOD  error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM/MOD  error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  underflow case - unable to initialize data stack\n");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthumslashmod(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthumslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM/MOD  address and maybe data missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UM/MOD  address and maybe data missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case UM/MOD 100 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthumslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  22 100 5 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 20)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  22 100 5 success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  22 100 5 success case lo - got wrong answer\n");
	}


	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  22 100 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x10000000000000000 0x10
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x10);

	dg_forthumslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000000000000000 0x10 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x1000000000000000)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000000000000000 0x10 success case - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000000000000000 0x10 success case - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000000000000000 0x10 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 20 7
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 7);

	dg_forthumslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  20 7 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  20 7 success case answer - got wrong answer \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 6)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  20 7 success case remainder - got wrong remainder \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  20 7 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case divide by 0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x10000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_forthumslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case lo - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case overflow
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1);

	dg_forthumslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case lo - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UM/MOD  0x10000 0x10000 1 overflow success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    	
}



void testdg_forthunloop ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing UNLOOP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to rstack case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_RSTACK_BUFFERID);

	dg_forthunloop(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthunloopname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNLOOP error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrstackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNLOOP error getting pointer to rstack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNLOOP error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 23984);

	dg_forthunloop(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthunloopname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNLOOP underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_rstackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNLOOP underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x55); // limit
	dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x20); // index

	dg_forthunloop(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNLOOP success case - got an error\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNLOOP success case - rstack length not 0 after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthuntil()
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
	
	UINT64 ccbufid = 0;
	
	UINT64 length = 0;
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing UNTIL\n");
#ifndef DGLU_NO_DIAPER	
	// error popping data stack case
	dg_initerrors(&BHarrayhead, 1000, &pError);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UNTIL error popping data stack case - unable to initialize error stack\n");
		return;
	}
	
	dg_forthuntil(&BHarrayhead); // error because there is no data space buffer for the variables yet
	
	pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forthuntilname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNTIL error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
    pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNTIL error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
    pError = dg_poperror(&BHarrayhead);
	
	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UNTIL error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
#endif	
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	ccbufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	length = dg_getbufferlength(&BHarrayhead, ccbufid);
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, length);
	
	dg_forthuntil(&BHarrayhead); 
	
	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UNTIL success case - got an error\n");
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthvariable ()
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

	UINT64 cibufid = 0;

	UINT64 wordlist = 0;

	Definitionheader* pdefinition = NULL;

	UINT64 length = 0;
	UINT64 dlength = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing VARIABLE\n");
#ifndef DGLU_NO_DIAPER
	// error doing create case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE error doing create case - unable to initialize error stack\n");
		return;
	}

	dg_forthvariable(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthvariablename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE error doing create case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcreatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE error doing create case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting data space buf id - if create worked, this should work

	// error growing data space buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASPACE_BUFFERID] );
	
	pBH->size = pBH->nextunusedbyte;
	pBH->growby = pBH->nextunusedbyte;
	pBH->maxsize = pBH->nextunusedbyte;

	dg_forthvariable(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthvariablename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE error growing data space buffer buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE error growing data space buffer buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE error growing data space buffer buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, DG_DATASPACE_BUFFERID);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	wordlist = dg_newwordlist(&BHarrayhead, 0);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dlength = dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID);

	//pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASPACE_BUFFERID] );

	//dg_printzerostring(&BHarrayhead, (unsigned char*)"size = %d\n", pBH->size);
	//dg_printzerostring(&BHarrayhead, (unsigned char*)"growby = %d\n", pBH->growby);
	//dg_printzerostring(&BHarrayhead, (unsigned char*)"maxsize = %d\n", pBH->maxsize);
	//dg_printzerostring(&BHarrayhead, (unsigned char*)"length = %d\n", pBH->nextunusedbyte);

	dg_forthvariable(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE success case - got an error \n");
	}

	if (length + 9 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE success case - current input offset pointer not after delimiter after first word\n");
	}

	pdefinition = dg_getpdefinition(&BHarrayhead, 0);

	if (pdefinition->dataoffset != dlength)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE success case - expected definition dataoffset to be old length of dataspace buffer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASPACE_BUFFERID) != dlength + sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE success case - expected dataspace buffer length to grow by sizeof UINT64\n");
	}

	// not checking to see if I passed in  pointer to name correctly here

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! VARIABLE success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);	
}


void testdg_forthword ()
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

	UINT64 cibufid = 0;
	UINT64* plength = NULL;
	unsigned char* pbuffer = NULL;

	UINT64 i = 0;

	UINT64 length = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing WORD\n");
#ifndef DGLU_NO_DIAPER
	// error popping delimiter character case
	dg_initbuffers(&BHarrayhead);

	dg_forthword(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error popping delimiter character case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error popping delimiter character case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error popping delimiter character case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting current interpret buffer case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)' ');

	dg_forthword(&BHarrayhead); // error because there is not variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting current interpret buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting current interpret buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting current interpret buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pcib
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer,9348);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)' ');

	dg_forthword(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentnewvariablebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting pointer to current input buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	// name length = 0 error 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)' ');

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_forthword(&BHarrayhead); // current interpret buffer is empty so namelength will be 0

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD no name error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_wordlength0error)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD no name error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// name too long error 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)' ');

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	for (i=0; i < 256; i++)
	{
		dg_pushbufferbyte(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 't');
	}

	dg_forthword(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD name too long error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_maxwordlengthexceedederror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD name too long error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to pwordbuf 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)' ');

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 8, (unsigned char*)"hi there");

	dg_freebuffer(&BHarrayhead, DG_WORD_BUFFERID);

	dg_forthword(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting pointer to wordbuffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting pointer to wordbuffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error getting pointer to wordbuffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// error growing wordbuffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)' ');

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	dg_pushbuffersegment(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 8, (unsigned char*)"hi there");

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_WORD_BUFFERID] );
	
	pBH->size = 0;
	pBH->growby = 0;
	pBH->maxsize = 0;

	dg_forthword(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error growing word buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthwordbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error growing word buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD error growing word buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	dg_pushbuffersegment(&BHarrayhead, cibufid, 15, (unsigned char*)"testname after");

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)' ');

	dg_forthword(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - got an error\n");
	}

	if (length + 9 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - current input offset pointer not after delimiter after first word\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_WORD_BUFFERID, &plength);

	if (pbuffer[1] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - word buffer first character not t\n");
	}

	if (pbuffer[8] != 'e')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - word buffer 7th character not e\n");
	}

	if (pbuffer[0] != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - word buffer 0th character not count\n");
	}

	if (*plength != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - length of word buffer not 9\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_WORD_BUFFERID, &plength);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)pbuffer)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - pointer to word buffer missing from data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// success case max length
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);

	cibufid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer);

	for (i=0; i < 255; i++)
	{
		dg_pushbufferbyte(&BHarrayhead, DG_TERMINALINPUT_BUFFERID, 't');
	}

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[cibufid] );

	length = pBH->currentoffset;

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x20);

	dg_forthword(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case - got an error\n");
	}

	if (length + 255 != pBH->currentoffset)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case max length - current input offset pointer not on delimiter after first word\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_WORD_BUFFERID, &plength);

	if (pbuffer[1] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case max length - word buffer first character not t\n");
	}

	if (pbuffer[255] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case max length - word buffer 256th character not t\n");
	}

	if (pbuffer[0] != 255)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case max length - word buffer 0th character not count\n");
	}

	if (*plength != 256)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case max length - length of word buffer not 256\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_WORD_BUFFERID, &plength);

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)pbuffer)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case max length - pointer to word buffer missing from data stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! WORD success case max length - data stack not empty after test\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthxor()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing XOR\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthxor(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthxorname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! OR underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthxor(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthxorname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF XOR 0x03C003C0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x03C00000000003C0);

	dg_forthxor(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR 0xFF0000FF XOR 0x03C003C0 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0xFCC000000000033F)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR 0xFF0000FF XOR 0x03C003C0 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR 0xFF0000FF XOR 0x03C003C0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 XOR 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthxor(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR -1 XOR 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != (UINT64)-2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR -1 XOR 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR -1 XOR 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 XOR 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthxor(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR 5 XOR 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR 5 XOR 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! XOR 5 XOR 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthleftbracket()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing [\n");
#ifndef DGLU_NO_DIAPER
	// error setting state variable case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! [ error setting state variable case - unable to initialize error stack\n");
		return;
	}

	dg_forthleftbracket(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthleftbracketname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! [ error setting state variable case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! [ error setting state variable case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_putbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! [ error setting state variable case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable, 88);

	dg_forthleftbracket(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! [ success case - error count not 0");
	}

	if (dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable) != (UINT64)dg_stateexecute)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! [ success case - state not execute\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! [ success case - data  stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthrightbracket()
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
	BHarrayhead.id = BHarrayheadid;

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ]\n");
#ifndef DGLU_NO_DIAPER
	// error setting state variable case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ] error setting state variable case - unable to initialize error stack\n");
		return;
	}

	dg_forthrightbracket(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrightbracketname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ] error setting state variable case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstatename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ] error setting state variable case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_putbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ] error setting state variable case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable, 88);

	dg_forthrightbracket(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ] success case - error count not 0");
	}

	if (dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable) != (UINT64)dg_statecompile)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ] success case - state not execute\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ] success case - data  stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

///////////////////////////////
// test core extension words //
///////////////////////////////

void testdg_forthzeronotequals()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 0<>\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthzeronotequals(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzeronotequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthzeronotequals(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzeronotequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF 0<> 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthzeronotequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 0xFF000000000000FF success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 0xFF000000000000FF success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 0xFF000000000000FF success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 0<>
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthzeronotequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> -1 success case - error count not 0 got \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> -1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> -1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 0<> 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthzeronotequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 5 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0<>
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthzeronotequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 0 success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 0 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0<> 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthzerogreater()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 0>\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0> error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthzerogreater(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzerogreatername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0> error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0> error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0> error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0> underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 1 element

	dg_forthzerogreater(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthzerogreatername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0> parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0> parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 0xFF0000FF 0> 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xFF000000000000FF);

	dg_forthzerogreater(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0xFF000000000000FF 0> success case - error count not\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0xFF000000000000FF 0> success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0xFF000000000000FF 0> success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 0>
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_forthzerogreater(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -1 0> success case - error count not 0\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -1 0> success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -1 0> success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 0> 
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthzerogreater(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{ 
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 5 0> success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 5 0> success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 5 0> success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0 0>
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthzerogreater(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0 0> success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0 0> success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 0 0> success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // success case 1 0>
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthzerogreater(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1 0> success case - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1 0> success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 1 0> success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthnotequals()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

    UINT64 testint = 0;
	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing <>\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthnotequals(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnotequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthnotequals(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnotequalsname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 <> 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthnotequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> 65536 <> 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> 65536 <> 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> 65536 <> 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 <> 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthnotequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> -1 <> 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> -1 <> 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> -1 <> 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 <> 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthnotequals(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> 5 <> 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> 5 <> 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! <> 5 <> 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_fortherase()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;
    unsigned char mybuf[20];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ERASE\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_fortherase(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_fortherasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_fortherase(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_fortherasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_popbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE parameters missing case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case erasing 2 at position 3
    dg_movebytes((unsigned char*)"abcdefghijklmnop", mybuf, 16); 
    
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&mybuf[3]);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_fortherase(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 2 at position 3 - error count not 0\n");
	}
    
    if (mybuf[3] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 2 at position 3 - 1st character not erased\n");
    }
    
    if (mybuf[4] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 2 at position 3 - 2nd character not erased\n");
    }
    
    if (mybuf[5] != 'f')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 2 at position 3 - character after end erased\n");
    }

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 2 at position 3 - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // success case erasing 0 at position 3
    dg_movebytes((unsigned char*)"abcdefghijklmnop", mybuf, 16); 
    
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&mybuf[3]);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_fortherase(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 0 at position 3 - error count not 0");
	}
    
    if (mybuf[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 0 at position 3 - 1st character erased\n");
    }
    
    if (mybuf[4] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 0 at position 3 - 2nd character erased\n");
    }

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing 0 at position 3 - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
    
    // success case erasing -1 at position 3
    dg_movebytes((unsigned char*)"abcdefghijklmnop", mybuf, 16); 
    
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)&mybuf[3]);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

	dg_fortherase(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing -1 at position 3 - error count not 0\n");
	}
    
    if (mybuf[3] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing -1 at position 3 - 1st character not erased\n");
    }
    
    if (mybuf[4] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing -1 at position 3 - 2nd character not erased\n");
    }

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ERASE success case erasing -1 at position 3 - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

void testdg_forthnip()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing NIP\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthnip(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnipname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthnip(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthnipname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) address and maybe data missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) address and maybe data missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);

	dg_forthnip(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 22)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 2
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-99);

	dg_forthnip(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) success case 2 - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-99)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) success case 2 - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! NIP (dg_forthnip) success case 2 - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    	
}


void testdg_forthroll()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing ROLL\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to the data stack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL - error getting current compile buffer case - unable to initialize error stack\n");
		return;
	}

	dg_forthroll(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrollname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthroll(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrollname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL underflow case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
    
    // underflow case 2
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthroll(&BHarrayhead); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthrollname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL underflow case 2 - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL underflow case 2 - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x12345678);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x9ABCDEF0);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x11223344);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x99aabbcc);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_forthroll(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case - got an error\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x9ABCDEF0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case - wrong number on top of stack\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x99aabbcc)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case - wrong number 2nd from top of stack\n");
	}
    
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x55667788)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case - wrong number 3rd from top of stack\n");
	}
    
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x11223344)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case - wrong number 4th from top of stack\n");
	}
    
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x12345678)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case - wrong number fifth from top of stack\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
    
    // 0 success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthroll(&BHarrayhead); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case 0 - got an error\n");
	}
    
    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! ROLL success case 0 - data stack not empty afterwards\n");
    }

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthugreaterthan()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);
	
	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing U>\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthugreaterthan(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthugreaterthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthugreaterthan(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthugreaterthanname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

	// success case 65536 U> 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);

	dg_forthugreaterthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> 65536 U> 20 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> 65536 U> 20 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> 65536 U> 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case -1 U> 1
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);

	dg_forthugreaterthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> -1 U> 1 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> -1 U> 1 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> -1 U> 1 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 5 U> 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthugreaterthan(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> 5 U> 5 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> 5 U> 5 success case - got wrong answer \n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! U> 5 U> 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

    
void testdg_forthudmslashmod ()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);
	BHarrayhead.maxsize = BHarraymaxsize;
	BHarrayhead.nextfreeindex = 0;
	BHarrayhead.pbuf = (void*)-1;
	BHarrayhead.size = 0;
	BHarrayhead.errorcount = 0;
	BHarrayhead.id = BHarrayheadid;

	const char* pError = NULL;
	UINT64 testint = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing UDM/MOD\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthumslashmod(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthumslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UMUDMMOD  error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  underflow case - unable to initialize data stack\n");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthumslashmod(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthumslashmodname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  address and maybe data missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  address and maybe data missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif

	// success case UM/MOD 100 5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

	dg_forthudmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  100 0 5 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0) // remainder
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  100 0 5 success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0) // numerator hi
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  100 0 5 success case lo - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 20) // numerator lo
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  100 0 5 success case lo - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  100 0 5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 0x10000000000000000 0x10
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x10);

	dg_forthudmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  0x10000000000000000 0x10 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0) // remainder
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  0x10000000000000000 0x10 success case - got wrong remainder\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0) // numerator hi
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  0x10000000000000000 0x10 success case - got wrong answer\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0x1000000000000000) // numerator lo
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  0x10000000000000000 0x10 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  0x10000000000000000 0x10 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case 20 7
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 7);

	dg_forthudmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  20 7 success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 6) // remainder
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  20 7 success case remainder - got wrong remainder\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0) // numerator hi
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  20 7 success case answer - got wrong answer\n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2) // numerator lo
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  20 7 success case answer - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! UDM/MOD  20 7 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case divide by 0
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x10000);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);

	dg_forthudmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD divide by 0 success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD divide by 0 success case lo - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD divide by 0 success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0xFFFFFFFFFFFFFFFF)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD divide by 0 success case hi - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD divide by 0 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

	// success case would overflow if this was um/mod
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1);

	dg_forthudmslashmod(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD  0 1 1 overflow success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD  0 1 1 overflow success case hi - got wrong remainder\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD  0 1 1 overflow success case hi - got wrong answer\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD  0x10000 0x10000 1 overflow success case lo - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! UDM/MOD  0x10000 0x10000 1 overflow success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthcompiles()
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
	INT64 myflag=5;
	
	unsigned char mysourcestring[12] = "hello there";
	
	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing COMPILE-S\n");
	
	// success case
	dg_initbuffers(&BHarrayhead);
	
	dg_initvariables(&BHarrayhead);
	
	mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - could not get current compile buffer\n");
		return;
	}
	
	mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - could not get current compile buffer's length\n");
		return;
	}
	
	// compiling a forth routine to push pointer to and length of a copy of a string to the data stack
	dg_compileinitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - could not compile init locals\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, UINT64(mysourcestring));
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - could not push address of source string to data stack\n");
		return;
	}
	
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 11);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - could not push length of source string to data stack\n");
		return;
	}
	
	dg_forthcompiles(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - could not do dg_forthcompiles got errors:\n");
		dg_forthdoterrors(&BHarrayhead);
		return;
	}	
	
	dg_compileexitlocals(&BHarrayhead);
	
	if (BHarrayhead.errorcount != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - could not compile exit locals\n");
		return;
	}
	
	// now the real test, does it crash?
	dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
	
	// seeing if it worked
	x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 2*sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - data stack length not correct after call\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - top number on data stack after executed compiled string code incorrect, length not same as source string\n");
		return;
	}
	
	x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
	
	if (x == (UINT64)mysourcestring)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - 2nd number on data stack after executed compiled string code incorrect, address of copy was same as source string\n");
		return;
	}
	
	if (dg_comparebytes(mysourcestring, 11, (unsigned char*)x, 11, &myflag) != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - compare of source string and copy failed\n");
		return;
	}
	
	if (myflag != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! testing COMPILE-S success case - string at reported address or copy not same as source string\n");
		return;
	}
	
	dg_clearerrors(&BHarrayhead);
	
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthpick()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;

    BHarrayhead.pisapiecb = (void*)-1;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing PICK\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to the datastack
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK error getting pointer to the datastack case - unable to initialize error stack\n");
		return;
	}

	dg_forthpick(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK error getting pointer to the datastack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK error getting pointer to the datastack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK error getting pointer to the datastack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 33);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 11);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_forthpick(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK underflow case - got wrong 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// empty data stack case (missing depth index)
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_forthpick(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK empty data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastacknoraddrmissingerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK empty data stack case - got wrong 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);


	// misaligned case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferbyte(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 33);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 11);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);

	dg_forthpick(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK  misaligned case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackmisalignederror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK  misaligned case - got wrong 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	// 1 value on stack underflow case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

	dg_forthpick(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpickname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK  value on stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK  value on stack underflow case - got wrong 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 33);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 11);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);

	dg_forthpick(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK success case - error count not 0");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 33)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK success case - got wrong value on top of stack\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 24)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! PICK success case - data  stack wrong length\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

void testdg_forthhex()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;

    BHarrayhead.pisapiecb = (void*)-1;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing HEX\n");
#ifndef DGLU_NO_DIAPER
	// error setting state variable case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HEX error setting state variable case - unable to initialize error stack\n");
		return;
	}

	dg_forthhex(&BHarrayhead); // error because there is no data space buffer for the variables yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthhexname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HEX error setting state variable case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthbasename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HEX error setting state variable case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_putbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HEX error setting state variable case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable, 88);

	dg_forthhex(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HEX success case - error count not 0");
	}

	if (dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, basevariable) != 16)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HEX success case - state not execute\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! HEX success case - data  stack not empty\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

void testdg_forthcmove ()
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

    unsigned char testbuff[20];

    UINT64 i = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CMOVE\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthcmove(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcmovename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 90832);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE underflow case - unable to initialize data stack");
        return;
    }

    dg_forthcmove(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcmovename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

    // illegal address error
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is an illegal address
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);

    dg_forthcmove(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcmovename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE illegal address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_movebytesforwardname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE illegal address case - got wrong error 1 below, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    


    // success case inc
    dg_initbuffers(&BHarrayhead);

    testint = 0;

    for (i = 0; i < 20; i++) // 12345678
    {                        // 12121218
        testbuff[i] = (unsigned char)i;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 1));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 3));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

    dg_forthcmove(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - error count not 0\n");
    }

    if (testbuff[3] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - wrong character dg_forthstored at position 3\n");
    }
    
    if (testbuff[4] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - wrong character dg_forthstored at position 4\n");
    }
    
    if (testbuff[5] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - wrong character dg_forthstored at position 5\n");
    }
    
    if (testbuff[6] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - wrong character dg_forthstored at position 6\n");
    }

    if (testbuff[7] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - wrong dg_forthstored at position 7\n");
    }

    if (testbuff[8] != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - character at position 8 was changed\n");
    }

    if (testbuff[2] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - character at position 0 was changed\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case - data stack not empty after test\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

    // success case dec
    dg_initbuffers(&BHarrayhead);

    testint = 0;

    for (i = 0; i < 20; i++)
    {
        testbuff[i] = (unsigned char)i;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 3));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 1));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

    dg_forthcmove(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case dec - error count not 0\n");
    }

    if (testbuff[1] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case dec - wrong character dg_forthstored at position 3\n");
    }

    if (testbuff[5] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case dec - wrong dg_forthstored at position 7\n");
    }

    if (testbuff[6] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case dec - character at position 8 was changed\n");
    }

    if (testbuff[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case dec - character at position 0 was changed\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE success case dec - data stack not empty after test\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}

void testdg_forthcmoveto ()
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

    unsigned char testbuff[20];

    UINT64 i = 0;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing CMOVE>\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthcmoveto(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcmovetoname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 90832);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> underflow case - unable to initialize data stack");
        return;
    }

    dg_forthcmoveto(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcmovetoname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

    // illegal address error
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); // hopefully this is an illegal address
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);

    dg_forthcmoveto(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcmovetoname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> illegal address case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_movebytesreversename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> illegal address case - got wrong error 1 below, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

    // illegal address error dec
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)testbuff);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-10); // hopefully this is an illegal address
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 10);

    dg_forthcmoveto(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthcmovetoname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> illegal address case dec- got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_movebytesreversename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> illegal address case dec- got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

    // success case inc
    dg_initbuffers(&BHarrayhead);

    testint = 0;

    for (i = 0; i < 20; i++)
    {
        testbuff[i] = (unsigned char)i;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 1));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 3));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

    dg_forthcmoveto(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case - error count not 0\n");
    }

    if (testbuff[3] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case - wrong character dg_forthstored at position 3\n");
    }

    if (testbuff[7] != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case - wrong dg_forthstored at position 7\n");
    }

    if (testbuff[8] != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case - character at position 8 was changed\n");
    }

    if (testbuff[2] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case - character at position 0 was changed\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case - data stack not empty after test\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    

    // success case dec
    dg_initbuffers(&BHarrayhead);

    testint = 0;

    for (i = 0; i < 20; i++) // 0123456789
    {                        // 0767676789
        testbuff[i] = (unsigned char)i;
    }

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 3));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(testbuff + 1));
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5);

    dg_forthcmoveto(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - error count not 0\n");
    }

    if (testbuff[1] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - wrong character stored at position 1\n");
    }
    
    if (testbuff[2] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - wrong character stored at position 2\n");
    }
    
    if (testbuff[3] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - wrong character stored at position 3\n");
    }
    
    if (testbuff[4] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - wrong character stored at position 4\n");
    }

    if (testbuff[5] != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - wrong stored at position 7\n");
    }

    if (testbuff[6] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - character at position 8 was changed\n");
    }

    if (testbuff[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - character at position 0 was changed\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! CMOVE> success case dec - data stack not empty after test\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    

    
}


void testdg_forthminusrot ()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing -ROT\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to the data stack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT error getting current compile buffer case - unable to initialize error stack\n");
        return;
    }

    dg_forthminusrot(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthminusrotname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT error getting pointer to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT error getting pointer to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT error getting pointer to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);

    dg_forthminusrot(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthminusrotname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
#endif
    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1234567811223344);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x9ABCDEF556677880);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x2288446613579864);

    dg_forthminusrot(&BHarrayhead); // error because there is no data stack yet

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT success case - got an error\n");
    }

    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x9ABCDEF556677880)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT success case - wrong number on top of stack\n");
    }

    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x1234567811223344)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT success case - wrong number 2nd top of stack\n");
    }

    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x2288446613579864)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT success case - wrong number 3rd top of stack\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! -ROT success case - data stack not empty after test\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthtworfrom ()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2R>\n");
#ifndef DGLU_NO_DIAPER
    // error popping rstack case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_forthtworfrom(&BHarrayhead); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtworfromname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_rstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // error pushing data stack
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x11223344);
    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x5566778899);

    pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[DG_DATASTACK_BUFFERID] );
    
    pBH->size = 0*sizeof(UINT64);
    pBH->growby = 0*sizeof(UINT64);
    pBH->maxsize = 0*sizeof(UINT64);

    dg_forthtworfrom(&BHarrayhead); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtworfromname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
#endif
    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x1122334455667788);
    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x123456789abcdef0);
    

    dg_forthtworfrom(&BHarrayhead); 

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> success case - got an error\n");
    }

    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x123456789abcdef0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> success case - wrong number on top of stack\n");
    }
    
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0x1122334455667788)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> success case - wrong number one below top of stack\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> success  case - data stack not empty after test\n");
    }

        if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R> success  case - rstack not empty after test\n");
    }


    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthtworfetch()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2R@\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to rstack case 
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_freebuffer(&BHarrayhead, DG_RSTACK_BUFFERID);

    dg_forthtworfetch(&BHarrayhead); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtworfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ error getting pointer to rstack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthrstackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ error getting pointer to rstack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_getpbuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ error getting pointer to rstack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // underflow case 
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_forthtworfetch(&BHarrayhead); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtworfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_rstackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ underflow case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // push datastack error error
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 00);
    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 30);

    dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

    dg_forthtworfetch(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtworfetchname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ push data stack error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ push data stack error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*) pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
#endif
    // success case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x8342739382834721);
    dg_pushbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID, 0x2299553399447711);

    dg_forthtworfetch(&BHarrayhead); 

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ success case - got an error\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x2299553399447711)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ success case - data stack didn't get right number\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x8342739382834721)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ success case - data stack didn't get right number\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

    if (testint != 0x2299553399447711)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ success case - rstack missing number\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

    if (testint != 0x8342739382834721)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ success case - rstack missing number\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ success case - data stack length not 0 after test\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2R@ success case - rstack length not 0 after test\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthtwotor()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2>R\n");
#ifndef DGLU_NO_DIAPER
    // error popping datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error popping data stack case - unable to initialize error stack");
        return;
    }

    dg_forthtwotor(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtwotorname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_popbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error popping data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);

    // error pushing rstack case
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);

    dg_freebuffer(&BHarrayhead, DG_RSTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error pushing rstack case - unable to initialize data stack");
        return;
    }

    dg_forthtwotor(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtwotorname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error pushing rstack case  - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthrstackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error pushing rstack case  - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_pushbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R error pushing rstack case  - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    

    

    // success case 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x55667788);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x112233445566);

    dg_forthtwotor(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

    if (testint != 0x112233445566)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R success case - got wrong number on top \n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_RSTACK_BUFFERID);

    if (testint != 0x55667788)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2>R success case - got wrong number one below top \n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R success case - data  stack not empty after calculation\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_RSTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! >R success case - rstack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthsynonym ()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    const char* pError;
    UINT64 testint = 0;

    Definitionheader* pdefinition;
    unsigned char* plstring;
    UINT64 lstringlength;
    
    Definitionheader* polddefinition;
    Definitionheader* pnewdefinition;
    

    unsigned char* pname1 = (unsigned char*)"\x002hi";
    unsigned char* pname2 = (unsigned char*)"\x001[";
    unsigned char* pname3 = (unsigned char*)"\x004OVER"; 
    
    UINT64 wordlist1;
    UINT64 word1;
    UINT64 word2;
    UINT64 word3;
    UINT64 oldwordid;
    UINT64 newwordid;
    // NOTE: I tried to use \x003DUP but MS took \x003D to be '=', which is not what the documentation says it does
    
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing SYNONYM\n");


    // fail case word not found
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

    //dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthstar),
        (unsigned char*)dg_forthstarname);

    dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentinterpretbuffer, DG_TERMINALINPUT_BUFFERID);
    
    dg_pushbuffersegment(
        &BHarrayhead, 
        DG_TERMINALINPUT_BUFFERID,
        7, 
        (unsigned char*)"moo cow");

    dg_forthsynonym(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SYNONYM success case word not found - error count 0\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case word 
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

    //dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    word1 = dg_new0stringnamecoreword(
        &BHarrayhead, 
        (UINT64)(&dg_forthdocompiletypealwaysexecute),
        (UINT64)(&dg_forthleftbracket),
        (unsigned char*)dg_forthleftbracketname);

    dg_linkdefinition(&BHarrayhead, wordlist1, word1);
    
    word2 = dg_new0stringnamecoreword(
        &BHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthover),
        (unsigned char*)dg_forthovername);

    dg_linkdefinition(&BHarrayhead, wordlist1, word2);
    
    word3 = dg_new0stringnamecoreword(
        &BHarrayhead, 
        (UINT64)(&dg_forthdocompiletypesubroutine),
        (UINT64)(&dg_forthstar),
        (unsigned char*)dg_forthstarname);

    dg_linkdefinition(&BHarrayhead, wordlist1, word3);
    
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
    

    dg_putbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentinterpretbuffer, 
        DG_TERMINALINPUT_BUFFERID);
        
    dg_putbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilewordlist, 
        wordlist1);
        
    dg_pushbuffersegment(
        &BHarrayhead, 
        DG_TERMINALINPUT_BUFFERID,
        5, 
        (unsigned char*)"* cow");

    dg_forthsynonym(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SYNONYM success case - error count not 0\n");
    }
    
    oldwordid = dg_finddefinsearchorder (
        &BHarrayhead,
        (unsigned char*)"*",
        1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SYNONYM success case dg_finddefinsearchorder oldword - error count not 0\n");
    }
        
    newwordid = dg_finddefinsearchorder (
        &BHarrayhead,
        (unsigned char*)"cow",
        3);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SYNONYM success case dg_finddefinsearchorder newword - error count not 0\n");
    }
    
    polddefinition = dg_getpdefinition(&BHarrayhead, oldwordid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SYNONYM success case getting pointer to old definition - error count not 0\n");
    }
    
    pnewdefinition = dg_getpdefinition(&BHarrayhead, newwordid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SYNONYM success case getting pointer to new definition - error count not 0\n");
    }
    
    if ((polddefinition->dataoffset != pnewdefinition->dataoffset) ||
        (polddefinition->databuf != pnewdefinition->databuf) || 
        (polddefinition->compileroutinebuf != pnewdefinition->compileroutinebuf) || 
        (polddefinition->compileroutineoffset != pnewdefinition->compileroutineoffset))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! SYNONYM success case new definition not same as old\n");
    }
    
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}
