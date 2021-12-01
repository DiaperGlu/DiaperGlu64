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

void testdg_forthdepthlstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdepthlstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthdepthlstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdepthlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring underflow case - unable to initialize data stack\n");
		return;
	}

	// could check where stack is corrupt, with just under 1 element
	dg_forthdepthlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdepthlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting lstring stack depth case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting lstring stack depth case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting pointer to buffer case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthdepthlstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdepthlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting lstring stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnumberoflstringsonstackname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring error getting lstring stack depth case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	
	dg_forthdepthlstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 2 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - address not what was expected\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdepthlstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthstartoffsetlstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstartoffsetlstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthstartoffsetlstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstartoffsetlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthstartoffsetlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstartoffsetlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting lstring start offset case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting lstring start offset case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting pointer to buffer case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthstartoffsetlstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstartoffsetlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting lstring start offset case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getlstringstartoffsetname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring error getting lstring start offset case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	
	dg_forthstartoffsetlstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - error count not 0 \n");
	} 

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 3 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - start offset not what was expected\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstartoffsetlstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthlengthlstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlengthlstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthlengthlstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlengthlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthlengthlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlengthlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting lstring start offset case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting lstring start offset case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting pointer to buffer case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthlengthlstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlengthlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting lstring start offset case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getlstringlengthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring error getting lstring start offset case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	
	dg_forthlengthlstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 4 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - length not what was expected\n");
	}
	
	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlengthlstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetslstringn ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetslstringn\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthgetslstringn(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError !=dg_forthgetslstringnname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthgetslstringn(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetslstringnname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting plstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting plstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthgetslstringn(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetslstringnname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	
	dg_forthgetslstringn(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - error count not 0 \n");
	}

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != 4 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - length not what was expected\n");
	}

	pBH = &( ( (Bufferhandle*)(BHarrayhead.pbuf) )[stringbufid] );

	testint = dg_popbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID);

	if (testint != ((UINT64)(pBH->pbuf)) + 3 )
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - address not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetslstringn success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgetlstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;
	UINT64 i = 0;

	unsigned char sbuf[80];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgetlstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthgetlstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthgetlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting plstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting plstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 3);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

	dg_forthgetlstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgetlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

	for (i=0; i<80; i++)
	{
		sbuf[i] = 'x';
	}
	
	dg_forthgetlstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - error count not 0 \n");
	}

	if (sbuf[0] != 'w')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[1] != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[2] != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[3] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[4] != 'x')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - sbuf not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthlstringtos ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;
	UINT64 i = 0;

	unsigned char sbuf[80];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthlstringtos\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthlstringtos(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlstringtosname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetlstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthlstringtos(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlstringtosname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting plstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting plstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

	dg_forthlstringtos(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthlstringtosname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_poplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);

	for (i=0; i<80; i++)
	{
		sbuf[i] = 'x';
	}
	
	dg_forthlstringtos(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - error count not 0 \n");
	}

	if (sbuf[0] != 'w')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[1] != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[2] != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[3] != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
	}

	if (sbuf[4] != 'x')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - sbuf not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthlstringtos success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthstolstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;
	UINT64 i = 0;

	unsigned char sbuf[80];

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthstolstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthstolstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstolstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthstolstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstolstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting plstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting plstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthstolstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthstolstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)sbuf);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);

	for (i=0; i<80; i++)
	{
		sbuf[i] = 'x';
	}

	sbuf[0] = 'z';
	sbuf[1] = 'q';
	
	dg_forthstolstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - error count not 0 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
	{
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - end offset of 1 not what was expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - end offset of 2 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 'z')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - string 2 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 8) != 'q')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - string 2 char 1 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthstolstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthgrowlstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthgrowlstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthgrowlstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgrowlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthgrowlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgrowlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error growing lstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthgrowlstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthgrowlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_growlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring error growing plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 2);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	
	dg_forthgrowlstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - error count not 0 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - end offset of 1 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgrowlstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthpicklstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthpicklstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthpicklstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpicklstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthpicklstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpicklstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring parameters missing case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error getting plstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 80);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthpicklstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthpicklstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_picklstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring error getting plstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);

	
	dg_forthpicklstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - error count not 0 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - end offset of 1 not what was expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - end offset of 2 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 7) != 'w')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - string 2 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 10) != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - string 2 char 3 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthpicklstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthdroplstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdroplstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthdroplstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdroplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");   
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");   
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");   
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthdroplstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdroplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error dropping lstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error dropping lstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthdroplstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdroplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error dropping lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_droplstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring error dropping lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}   

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	
	dg_forthdroplstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - error count not 0 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - string buffer not balanced after calculation,\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'h')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - string 2 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 'y')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - string 2 char 1 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdroplstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// should check case where stuff pushed into buffer isn't a multiple of element size
}


void testdg_forthdeletelstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthdeletelstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthdeletelstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeletelstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthdeletelstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeletelstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error deleting lstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error dropping lstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthdeletelstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdeletelstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error deleting lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_deletelstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error deleting lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	
	dg_forthdeletelstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - error count not 0 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'w')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 2 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 't')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 2 char 1 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"zq");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	
	dg_forthdeletelstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - error count not 0 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - end offset of 1 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'h')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 0 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 'y')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 0 char 1 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 3) != 'z')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 1 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 4) != 'q')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - string 1 char 1 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthinsertlstring ()
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

	UINT64 offsetbufid = 0;
	UINT64 stringbufid = 0;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthinsertlstring\n");
#ifndef DGLU_NO_DIAPER
	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthinsertlstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthinsertlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error inserting lstring case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdeletelstring error dropping lstring case - unable to initialize data stack\n");
		return;
	}

	//bufid = dg_newbuffer(&BHarrayhead, 100, 100, &pError, false);

	//if (pError != dg_success)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! getbuffersize2 error getting plstring case - unable to initialize test buffer\n");
	//}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 39847);

	dg_forthinsertlstring(&BHarrayhead);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthinsertlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error inserting lstring case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_insertlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring error inserting lstring case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
#endif
	// success case 1
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5); // length
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 0); // index
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	
	dg_forthinsertlstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - error count not 0, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - end offset of 0 not what was expected\n");
	}

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - end offset of 0 not what was expected\n");
	}

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 5) != 'h')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - string 2 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 8) != 'w')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - string 2 char 1 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	// success case 2
	dg_initbuffers(&BHarrayhead);

	offsetbufid = dg_newbuffer(&BHarrayhead, 100, 200, &pError, false);
	
	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	stringbufid = dg_newbuffer(&BHarrayhead, 1000, 2000, &pError, false);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 1 - unable to initialize test buffer\n");
		return;
	}

	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 3, (unsigned char*)"hey");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 4, (unsigned char*)"woot");
	dg_pushlstring(&BHarrayhead, offsetbufid, stringbufid, 2, (unsigned char*)"zq");

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 5); // length
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 1); // offset
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, offsetbufid);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, stringbufid);
	
	dg_forthinsertlstring(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - error count not 0 \n");
	}

	if (dg_getbufferlength(&BHarrayhead, stringbufid) != 14)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string buffer not balanced after calculation\n");
	}

	if (dg_getnumberoflstringsonstack(&BHarrayhead, offsetbufid) != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - lstring stack not balanced after calculation\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 0) != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 0 not what was expected\n");
	}

	if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 8) != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 1 not what was expected\n");
	}

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 16) != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 2 not what was expected\n");
	}

    if (dg_getbufferuint64(&BHarrayhead, offsetbufid, 24) != 14)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - end offset of 3 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 0) != 'h')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 0 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 2) != 'y')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 0 char 1 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 8) != 'w')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 2 char 0 not what was expected\n");
	}

	if (dg_getbufferbyte(&BHarrayhead, stringbufid, 9) != 'o')
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - string 2 char 1 not what was expected\n");
	}

	if (dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthinsertlstring success case 2 - data  stack not balanced after calculation\n");
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

/*
void testdg_forthcscanlstring ()
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

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthcscanlstring\n");

	// error getting pointer to datastack case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - unable to initialize error stack\n");
		return;
	}

	dg_forthcscanlstring(&BHarrayhead); // error because there is no data stack yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcscanlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthdatastackbufferidname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring error getting pointer to data stack case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");  
	}

	dg_clearerrors(&BHarrayhead);

	dg_freeallbuffers(&BHarrayhead);

	
	// underflow case
	dg_initbuffers(&BHarrayhead);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring underflow case - unable to initialize data stack\n");
		return;
	}

	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
	dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);
    dg_pushbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, 29384);

	// could check where stack is corrupt, with just under 1 element
	dg_forthcscanlstring(&BHarrayhead);

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_forthcscanlstringname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring parameters missing case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_datastackunderflowerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthcscanlstring parameters missing case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
	}

	dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);

	
	// error cscanning lstring case

}
*/

// dg_forthscanlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing scan case
//  success case

// dg_forthshortenlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing shorten case
//  success case

// dg_forthnewlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing new case
//  success case

// dg_forthrolllstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing roll case
//  success case

// dg_forthminusrolllstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing minusroll case
//  success case

// dg_forthdeleteinlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing deletein case
//  success case

// dg_forthinsertinlstring
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing insertin case
//  success case

// dg_forthcatlstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_catlstringn case
//  success case

// dg_forthcopystolstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copystolstringn case
//  success case

// dg_forthcopysfromlstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copysfromlstringn case
//  success case

// dg_forthsetlengthlstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_setlengthlstringn case
//  success case

// dg_forthcopystoreplacelstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copystoreplacelstringn case
//  success case

// dg_forthcopylstringntoreplacelstringn
//  error getting pointer to datastack case
//  datastack underflow case
//  error doing dg_copylstringntoreplacelstringn case
//  success case


