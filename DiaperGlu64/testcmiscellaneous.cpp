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
#include "testdglu.h"


void testdg_evaluatebuffer()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	const char* pError = NULL;

	unsigned char* pbuffer = NULL;
	UINT64* plength = NULL;

	UINT64* pints = NULL;

	UINT64 definition = 0;


	UINT64 bufferid = 0;
    
    UINT64 wordlist1;
    UINT64 wordlist2;
    UINT64 wordlist3;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_evaluatebuffer\n");
#ifndef DGLU_NO_DIAPER
	// error getting pbuffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_evaluatebuffer(&BHarrayhead, 837); // 873  should be the number of an invalid buffer

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_evaluatebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error getting pointer to the buffer case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentinputbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error getting pointer to the buffer case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error getting pointer to the buffer case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
#endif

	// error putting to current interpret buffer
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	bufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer unable to initialize a buffer for the test\n");
		return;
	}

	dg_pushbuffersegment(&BHarrayhead, bufferid, 20, (unsigned char*)"holy moly quacamole!");

	dg_freebuffer(&BHarrayhead, DG_DATASPACE_BUFFERID);

	dg_evaluatebuffer(&BHarrayhead, bufferid); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_evaluatebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error putting to current input buffer variable case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpcurrentinputbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error putting to current input buffer variable case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name) // changed for v5.3 
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error putting to current input buffer variable case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// error getting base - this test assumes base variable comes after current input buffer variable
      // removed test temporarily because dg_finddefinwordlist now uses variables that are after base in DG_DATASPACE_BUFFER
	//dg_initbuffers(&BHarrayhead);

	//dg_initvariables(&BHarrayhead);

	//bufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer unable to initialize a buffer for the test\n");
	//	return;
	//}

	//dg_pushbuffersegment(&BHarrayhead, bufferid, 20, (unsigned char*)"holy moly quacamole!");

	//pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	//*plength = basevariable;

	//dg_evaluatebuffer(&BHarrayhead, bufferid); 

	//pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_evaluatebuffername)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error getting base variable case - got wrong error on top, got ");
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

    //pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_forthbasename)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error getting base variable case - got wrong error 1 below top, got ");
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

   // pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_getbufferuint64name)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error getting base variable case - got wrong error 2 below top, got ");
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

    //dg_freeallbuffers(&BHarrayhead);

    //dg_clearerrors(&BHarrayhead);

    // error pushing number to the data stack
    dg_initbuffers(&BHarrayhead);

    dg_initvariables(&BHarrayhead);
 
    dg_inithlists(&BHarrayhead);   

    bufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer unable to initialize a buffer for the test\n");
        return;
    }

    dg_pushbuffersegment(&BHarrayhead, bufferid, 20, (unsigned char*)"1234 holy quacamole!");

    dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);

    dg_evaluatebuffer(&BHarrayhead, bufferid); 

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_evaluatebuffername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error pushing number to the data stack - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_docolorstatenname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error pushing number to the data stack - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error pushing number to the data stack - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// error getting the state variable - don't know how to test this case since state comes before base

	// error doing dg_forthliteral
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
 
    dg_inithlists(&BHarrayhead);   

	bufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer unable to initialize a buffer for the test\n");
		return;
	}

	dg_pushbuffersegment(&BHarrayhead, bufferid, 20, (unsigned char*)"1234 holy quacamole!");

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 283);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable, (UINT64)dg_statecompile);

	dg_evaluatebuffer(&BHarrayhead, bufferid); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_evaluatebuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error compiling push number to the data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_docolorstatenname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error compiling push number to the data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_compilepushntodatastackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer error compiling push number to the data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// test error find def in search order

	// test error executing
	
	// test success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	bufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer unable to initialize a buffer for the test\n");
		return;
	}

	dg_pushbuffersegment(&BHarrayhead, bufferid, 14, (unsigned char*)"1234 heybea hi");

	wordlist1 = dg_newwordlist(&BHarrayhead, 0); // 1

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist1); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 451, (unsigned char*)"heybea", 6); // 2
	definition = dg_createconstantdef(&BHarrayhead, 661, (unsigned char*)"hia", 3); // 2
	definition = dg_createconstantdef(&BHarrayhead, 7771, (unsigned char*)"hoybea", 6); // 3

	wordlist2 = dg_newwordlist(&BHarrayhead, 0); // 4

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist2); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 452, (unsigned char*)"heybeb", 6); // 5
	definition = dg_createconstantdef(&BHarrayhead, 662, (unsigned char*)"hib", 3); // 6
	definition = dg_createconstantdef(&BHarrayhead, 7772, (unsigned char*)"hoybeb", 6); // 7
    
	wordlist3 = dg_newwordlist(&BHarrayhead, 0); // 8

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist3); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 9
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 10
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"hoybe", 5); // 11

	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist2);
	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist3);


	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 283);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable, (UINT64)dg_stateexecute);

	dg_evaluatebuffer(&BHarrayhead, bufferid); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer success case - unable to get pointer to the data stack \n");
	}

	if (*plength != 3 * sizeof(UINT64))
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer success case - didn't get exactly 3 items on the data stack\n");
		return;
	}

	pints = (UINT64*)pbuffer;

	if (pints[0] != 1234)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer success case - expected 1234 to be first on data stack\n");
	}

	if (pints[1] != 451)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer success case - expected 451 to be second on data stack\n");
	}

	if (pints[2] != 66)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer success case - expected 66 to be third on stack\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// word not found case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	bufferid = dg_newbuffer(&BHarrayhead, 1000, 1000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_evaluatebuffer unable to initialize a buffer for the test\n");
		return;
	}

	dg_pushbuffersegment(&BHarrayhead, bufferid, 20, (unsigned char*)"1234 holy quacamole!");

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 283);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable, (UINT64)dg_stateexecute);

	dg_evaluatebuffer(&BHarrayhead, bufferid); 

	dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_evaluatebufferwordnotfounderror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_evaluatebuffer word not found case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_hibit()
{
    UINT64 index;
    
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_hibitd\n");

    // 0 case
	index = dg_hibitd(
        0,
        0);

	if (index != largestunsignedint)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_hitbitd 0 case, got wrong index, expected -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, index);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    // 1 case
    index = dg_hibitd(
        1,
        0);

	if (index != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_hitbitd 1 case, got wrong index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, index);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
 
    // 2 case
    index = dg_hibitd(
        2,
        0);

	if (index != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_hitbitd 2 case, got wrong index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, index);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
 
    // 3 case
    index = dg_hibitd(
        3,
        0);

	if (index != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_hitbitd 3 case, got wrong index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, index);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
 
    // 4 case
    index = dg_hibitd(
        4,
        0);

	if (index != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_hitbitd 4 case, got wrong index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, index);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
 
    // 2^64 case
    index = dg_hibitd(
        0,
        1);

	if (index != 64)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_hitbitd 2^64 case, got wrong index, expected 64, got ");
        dg_writestdoutuinttodec(&BHarrayhead, index);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	} 
 
    // 2^127 case
    index = dg_hibitd(
        0,
        0x8000000000000000);

	if (index != 127)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_hitbitd 2^127 case, got wrong index, expected 127, got ");
        dg_writestdoutuinttodec(&BHarrayhead, index);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}      
}


void testdg_ubitsmask()
{
    UINT64 mask;
    
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_ubitsmask\n");

    // 0 bits mask case
    mask = dg_ubitsmask(0);

    if (mask != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_ubitsmask 0 case, got wrong mask, expected 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // 1 bits mask case
    mask = dg_ubitsmask(1);

    if (mask != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_ubitsmask 1 case, got wrong mask, expected 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // 2 bits mask case
    mask = dg_ubitsmask(2);

    if (mask != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_ubitsmask 2 case, got wrong mask, expected 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // 3 bits mask case
    mask = dg_ubitsmask(3);

    if (mask != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_ubitsmask 3 case, got wrong mask, expected 7, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // 4 bits mask case
    mask = dg_ubitsmask(4);

    if (mask != 0x0f)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_ubitsmask 4 case, got wrong mask, expected 0x0f, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // 0x40 bits mask case
    mask = dg_ubitsmask(0x40);

    if (mask != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_ubitsmask 0x40 case, got wrong mask, expected largestunsignedint, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mask);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}

