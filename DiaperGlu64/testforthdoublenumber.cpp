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

/*
void testdg_forthdstar()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D*\n");

	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthdstar(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* error getting pointer to data stack case - got wrong error 1 below top, got ");
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
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthdstar(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdstarname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* address and maybe data missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* address and maybe data missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 100 * 22
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 100);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 22);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

	dg_forthdstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 22 * 100 success case - error count not 0");
	}
 
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 22 * 100 success case - got wrong answer\n");
    }   

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 2200)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 22 * 100 success case - got wrong answer\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 22 * 100 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case -2 * -5
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-5);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   

	dg_forthdstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* -2 * -5 success case - error count not 0");
	}
 
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* -2 * -5 success case - got wrong answer hi\n");
    }   

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* -2 * -5 success case - got wrong answer lo\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* -2 * -5 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 3 * -7
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   

	dg_forthdstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 success case - error count not 0");
	}
 
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 success case - got wrong answer hi\n");
    }   

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 success case - got wrong answer lo\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 3 * -7 b
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-7);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   

	dg_forthdstar(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 b success case - error count not 0");
	}
 
    if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 b success case - got wrong answer hi\n");
    }

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != (UINT64)-21)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 b success case - got wrong answer lo\n");
	}

	if (dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID) != 55)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 b success case - data stack corrupted\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D* 3 * -7 b success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);	
}
*/

void testdg_forthdplus()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D+\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ error getting pointer to data stack case - unable to initialize error stack");
		return;
	}

	dg_forthdplus(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ error getting pointer to data stack case - got wrong error on top, got ");
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
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ underflow case - unable to initialize data stack");
		return;
	}

	// could check where stack is corrupt, with just under 2 elements

	dg_forthdplus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdplusname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 65536 + 20
	dg_initbuffers(&BHarrayhead);

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

	dg_forthdplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ 65536 + 20 success case - error count not 0");
	}
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ 65536 + 20 success case - got wrong answer hi\n");
    }   

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 65556)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ 65536 + 20 success case - got wrong answer lo\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ 65536 + 20 success case - data  stack not empty after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


    // success case -1 + 1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdplus(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 + 1 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 + 1 success case - got wrong answer hi\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 + 1 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ =-1 + 1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


	// success case -1 + 1 not 128 bit aligned
	dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

	dg_forthdplus(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 + 1 not 128 bit aligned success case - error count not 0");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 + 1 not 128 bit aligned success case - got wrong answer hi\n");
	}
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 + 1 not 128 bit aligned success case - got wrong answer lo\n");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 + 1 not 128 bit aligned success case - got wrong number before answer\n");
    }  
    
     if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
     {
         dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ =-1 + 1 not 128 bit aligned success case - data  stack not empty after calculation\n");
     }

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

}


void testdg_forthdminus()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D-\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdminus(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdminusname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdminus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdminusname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 65536 - 20
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdminus(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- 65536 + 20 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D- 65536 + 20 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 65516)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ 65536 - 20 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ 65536 - 20 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case -1 - 1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdminus(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 - 1 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 - 1 success case - got wrong answer hi\n");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 - 1 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0 -1 - 1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    

    // success case -1 - 1 not 128 bit aligned
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 66);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdminus(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 - 1 not 128 bit aligned success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 - 1 not 128 bit aligned success case - got wrong answer hi\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 - 1 not 128 bit aligned success case - got wrong answer lo\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 66)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D+ -1 - 1 not 128 bit aligned success case - got wrong number after answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0 -1 - 1 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdequals()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D=\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdequals(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdequalsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdequals(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdequalsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 65536 == 20
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdequals(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 65536 == 20 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 65536 == 20 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 65536 == 20 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case 1 == 1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdequals(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 1 == 1 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 1 == 1 success case - got wrong answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 1 == 1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case 1 == 1 not 128 bit aligned
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdequals(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 1 == 1 not 128 bit aligned success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 1 == 1 not 128 bit aligned success case - got wrong answer\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 1 == 1 not 128 bit aligned success case - got wrong number after answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D= 1 == 1 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdzeroless()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D0<\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdzeroless(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdzerolessname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdzeroless(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdzerolessname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 0
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdzeroless(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< 0 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< 0 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< 0 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case -1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -1);     

    dg_forthdzeroless(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< -1 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< -1 success case - got wrong answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< -1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case -1 not 128 bit aligned
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -1);     

    dg_forthdzeroless(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< -1 not 128 bit aligned success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< -1 not 128 bit aligned success case - got wrong answer\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< -1 not 128 bit aligned success case - got wrong answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0< -1 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdzeroequals()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D0=\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdzeroequals(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdzeroequalsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdzeroequals(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdzeroequalsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 0
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdzeroequals(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= 0 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= 0 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= 0 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case -1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -1);     

    dg_forthdzeroequals(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= -2 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= -2 success case - got wrong answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= -2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    
    // success case -1 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, -1);     

    dg_forthdzeroequals(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= -2 not 128 bit aligned success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= -2 not 128 bit aligned success case - got wrong answer\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= -2 not 128 bit aligned success case - got wrong number after answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D0= -2 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdtwostar()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D2*\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdtwostar(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdtwostarname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdtwostar(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdtwostarname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 0x1000200080004000C000100010001000
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xC000100010001000);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1000200080004000);
         
    dg_forthdtwostar(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x2000400100008001)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x8000200020002000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case 0x1000200080004000C000100010001000 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0xC000100010001000);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1000200080004000);
        
    dg_forthdtwostar(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case not 128 bit aligned - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x2000400100008001)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case not 128 bit aligned - got wrong answer hi\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0x8000200020002000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case not 128 bit aligned - got wrong answer lo\n");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case not 128 bit aligned - got wrong number after answer\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2* 0x1000200080004000C000100010001000 success case not 128 bit aligned - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdtwoslash()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D2/\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdtwoslash(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdtwoslashname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdtwoslash(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdtwoslashname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 0x1000200080004000C000100010001000
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x4000100010001000);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x8000200080004001);
         
    dg_forthdtwoslash(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0xC000100040002000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0xA000080008000800)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case 0x1000200080004000C000100010001000 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x4000100010001000);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x8000200080004001);
        
    dg_forthdtwoslash(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case not 128 bit aligned - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0xC000100040002000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case not 128 bit aligned - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0xA000080008000800)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case - got wrong answer lo\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case not 128 bit aligned - got wrong number after answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D2/ 0x1000200080004000C000100010001000 success case not 128 bit aligned - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdabs()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DABS\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdabs(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdabsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdabs(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdabsname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case -2
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
         
    dg_forthdabs(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS -2 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS -2 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS -2 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS -2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


    // success case 2
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
            
    dg_forthdabs(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 2 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
            
    dg_forthdabs(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 not 128 bit aligned success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 not 128 bit aligned success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 not 128 bit aligned success case - got wrong answer lo\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 not 128 bit aligned success case - got number after answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DABS 2 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdnegate()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DNEGATE\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdnegate(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdnegatename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdnegate(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdnegatename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case -2
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
         
    dg_forthdnegate(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE -2 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE -2 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE -2 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE -2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


    // success case 2
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
            
    dg_forthdnegate(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case 2 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
            
    dg_forthdnegate(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 not 128 bit aligned success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 not 128 bit aligned success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 not 128 bit aligned success case - got wrong answer lo\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 not 128 bit aligned success case - got wrong number after answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DNEGATE 2 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthmstarplus()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing M*/\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthmstarslash(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthmstarslashname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthmstarslash(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthmstarslashname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 20 0 4 2
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);   

    dg_forthmstarslash(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 40)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case 20 0 4 2 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 4);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);   

    dg_forthmstarslash(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 not 128 bit aligned success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 not 128 bit aligned success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 40)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 not 128 bit aligned success case - got wrong answer lo\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 not 128 bit aligned success case - got wrong number after answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M*/ 20 0 4 2 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdtos()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D>S\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdtos(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdtosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdtos(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdtosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case -2
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
         
    dg_forthdtos(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S -2 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S -2 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S -2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case too big positive
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)1);
            
    dg_forthdtos(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S 0 1 success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)0x7FFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S 0 1 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S 0 1 success case - data  stack not empty after calculation\n");
    }

    // success case 5
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)5);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)0);
            
    dg_forthdtos(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S 5 success case - error countnot 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S 5 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S 5 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

   // success case -2 not 128 bit aligned 
   dg_initbuffers(&BHarrayhead);

   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)55);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
        
   dg_forthdtos(&BHarrayhead);

   if (dg_geterrorcount(&BHarrayhead) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S -2 not 128 bit aligned success case - error count not 0");
   }

   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != (UINT64)-2)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S -2 not 128 bit aligned success case - got wrong answer\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
   
   if (testint != (UINT64)55)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S -2 not 128 bit aligned success case - got wrong number after answer\n");
   }   

   if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D>S -2 not 128 bit aligned success case - data  stack not empty after calculation\n");
   }

   dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdmax()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DMAX\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdmax(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdmaxname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdmax(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdmaxname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 65536 20
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdmax(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX 65536 20 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX 65536 20 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 65536)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX 65536 20 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX 65536 20 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case -1 1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdmax(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1 1 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1 1 success case - got wrong answer hi\n");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1 1 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1  1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    

   // success case -1 1 not 128 bit aligned 
   dg_initbuffers(&BHarrayhead);

   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)55);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

   dg_forthdmax(&BHarrayhead);

   if (dg_geterrorcount(&BHarrayhead) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1 1 not 128 bit aligned success case - error count not 0");
   }

   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1 1 not 128 bit aligned success case - got wrong answer hi\n");
   }

   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 1)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1 1 not 128 bit aligned success case - got wrong answer lo\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 55)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1 1 not 128 bit aligned success case - got wrong number after answer\n");
   }

   if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMAX -1  1 not 128 bit aligned success case - data  stack not empty after calculation\n");
   }

   dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdmin()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DMIN\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdmin(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdminname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdmin(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdminname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 65536 20
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdmin(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN 65536 20 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN 65536 20 success case - got wrong answer hi\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN 65536 20 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN 65536 20 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case -1 1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

    dg_forthdmin(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1 1 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1 1 success case - got wrong answer hi\n");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1 1 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1  1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

   // success case -1 1 not 128 bit aligned 
   dg_initbuffers(&BHarrayhead);

   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)55);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   

   dg_forthdmin(&BHarrayhead);

   if (dg_geterrorcount(&BHarrayhead) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1 1 not 128 bit aligned success case - error count not 0");
   }

   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != -1)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1 1 not 128 bit aligned success case - got wrong answer hi\n");
   }

   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != -1)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1 1 not 128 bit aligned success case - got wrong answer lo\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 55)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1 1 not 128 bit aligned success case - got wrong number after answer\n");
   }

   if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DMIN -1  1 not 128 bit aligned success case - data  stack not empty after calculation\n");
   }

   dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthmplus()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing M+\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthmplus(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthmplusname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthmplus(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthmplusname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 65536 20
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
   

    dg_forthmplus(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ 65536 20 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ 65536 20 success case - got wrong answer hi\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 65556)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ 65536 20 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ 65536 20 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case -1 1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);   

    dg_forthmplus(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1 1 success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1 1 success case - got wrong answer hi\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1 1 success case - got wrong answer lo\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1  1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case -1 1 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);   

    dg_forthmplus(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1 1 not 128 bit aligned success case - error count not 0");
    }

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1 1 not 128 bit aligned success case - got wrong answer hi\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1 1 not 128 bit aligned success case - got wrong answer lo\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1 1 not 128 bit aligned success case - got wrong number after answer\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! M+ -1  1 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdlessthan()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D<\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdlessthan(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdlessthanname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdlessthan(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdlessthanname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 0 0
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);  

    dg_forthdlessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 0 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 0 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 0 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case -1 0
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);  

    dg_forthdlessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< -1 0 success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< -1 0 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< -1 0 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case 0 -1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

    dg_forthdlessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 -1 success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 -1 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 -1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // success case 0 -1 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

    dg_forthdlessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 -1 not 128 bit aligned success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 -1 not 128 bit aligned success case - got wrong answer\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)55)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 -1 not 128 bit aligned success case - got wrong number after answer\n");
    } 

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D< 0 -1 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthdulessthan()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing DU<\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthdulessthan(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdulessthanname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthdulessthan(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdulessthanname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 0 0
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);  

    dg_forthdulessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 0 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 0 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 0 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case -1 0
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);  

    dg_forthdulessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< -1 0 success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< -1 0 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< -1 0 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case 0 -1
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

    dg_forthdulessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 -1 success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 -1 success case - got wrong answer\n");
    }   

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 -1 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    // success case 0 -1 not 128 bit aligned 
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);

    dg_forthdulessthan(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 -1 not 128 bit aligned success case - error count not 0");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 -1 not 128 bit aligned success case - got wrong answer\n");
    }
    
      testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

      if (testint != (UINT64)55)
      {
          dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 -1 not 128 bit aligned success case - got wrong number after answer\n");
      } 

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! DU< 0 -1 not 128 bit aligned success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthtworot()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing 2ROT\n");
#ifndef DGLU_NO_DIAPER
    // error getting pointer to datastack case
    dg_initerrors(&BHarrayhead, 1000, &pError);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT error getting pointer to data stack case - unable to initialize error stack");
        return;
    }

    dg_forthtworot(&BHarrayhead); // error because there is no data stack yet

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtworotname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT error getting pointer to data stack case - got wrong error on top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT underflow case - unable to initialize data stack");
        return;
    }

    // could check where stack is corrupt, with just under 2 elements

    dg_forthtworot(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtworotname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
    // success case 65536 + 20
    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);   
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); 
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 40);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3); 

    dg_forthtworot(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - error count not 0");
    }
 
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer on top\n");
    }   

    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 65536)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 1 below top\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 2 below top\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 40)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 3 below top\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 4 below top\n");
    }
    
    testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (testint != 20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 5 below top\n");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

   // success case 65536 + 20 not 128 bit aligned 
   dg_initbuffers(&BHarrayhead);

   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 55);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 65536);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);   
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 20);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2); 
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 40);
   dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3); 

   dg_forthtworot(&BHarrayhead);

   if (dg_geterrorcount(&BHarrayhead) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 not 128 bit aligned success case - error count not 0");
   }

   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 1)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 not 128 bit aligned success case - got wrong answer on top\n");
   }   

   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 65536)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 not 128 bit aligned success case - got wrong answer 1 below top\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 3)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 2 below top\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 40)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 3 below top\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 2)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 4 below top\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 20)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong answer 5 below top\n");
   }
   
   testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

   if (testint != 55)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - got wrong number after answer\n");
   }

   if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
   {
       dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2ROT 65536 1 20 2 40 3 success case - data  stack not empty after calculation\n");
   }

   dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthddot()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D.\n");

    // success case -2
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1);    

    dg_printzerostring(&BHarrayhead, (unsigned char*)" should see >>>-2 <<<, got >>>");
    dg_forthddot(&BHarrayhead);
    dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D. -2 success case - error count not 0");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D. -2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthddotr()
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

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing D.R\n");

    // success case -2
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-2);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)-1); 
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)5);   

    dg_printzerostring(&BHarrayhead, (unsigned char*)" should see >>>   -2<<<, got >>>");
    dg_forthddotr(&BHarrayhead);
    dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D.R -2 success case - error count not 0");
    }

    if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! D.R -2 success case - data  stack not empty after calculation\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthtwoliteral ()
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

    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing 2LITERAL\n");
#ifndef DGLU_NO_DIAPER
    // error getting current compile buffer
    dg_initbuffers(&BHarrayhead);

    dg_forthtwoliteral(&BHarrayhead);  // variables not initialized

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtwoliteralname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL error getting current compile buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthswapname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL error getting current compile buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

    // error popping data stack case
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);

    dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

    dg_forthtwoliteral(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthtwoliteralname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_forthswapname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL error popping data stack case - got wrong error 1 below top, got ");
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
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - could not get current compile buffer\n");
        return;
    }
    
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - could not get current compile buffer's length\n");
        return;
    }
    
    // compiling a forth routine to push a number to the data stack
    dg_compileinitlocals(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - could not compile init locals\n");
        return;
    }
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x1165239486756633);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - could not push 1st test number to data stack\n");
        return;
    }
    
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0x9988776655443322);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - could not push 2nd test number to data stack\n");
        return;
    }
    
    
    dg_forthtwoliteral(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - could not do dg_forthtwoliteral\n");
        return;
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - dg_forthtwoliteral did not consume data stack parameter\n");
        return;
    }
    
    dg_compileexitlocals(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - could not compile exit locals\n");
        return;
    }
    
    // now the real test, does it crash?
    dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
    
    // seeing if it worked
    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 2 * sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - data stack length not correct after call\n");
        return;
    }
    
    x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 0x9988776655443322)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - top number on data stack after calling compiled LITERAL incorrect\n");
        return;
    }
    
    x = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 0x1165239486756633)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! 2LITERAL success case - 2nd number on data stack after calling compiled LITERAL incorrect\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
}


