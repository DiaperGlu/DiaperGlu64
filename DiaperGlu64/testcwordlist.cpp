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

void testdg_newwordlist()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 vocabid = 0;

	const char* pError = NULL;

//	unsigned char* pbuffer = NULL;
//	UINT64* plength = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newwordlist\n");
#ifndef DGLU_NO_DIAPER
	// error making new hlist element case
	dg_initerrors(&BHarrayhead, 1000, &pError);

	if (pError != dg_success)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - error making new hlist element case - unable to initialize error stack");
		return;
	}

	vocabid = dg_newwordlist(&BHarrayhead, 0); // error because there is no vocabulary buffer yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_newwordlistname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - create new vocabulary push to vocab buffer error case - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_newhlistelementname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - create new vocabulary push to vocab buffer error case - got wrong error 1 below top");
	}

	if (vocabid != DG_MAX_WORDLISTID)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - create new vocabulary push to vocab buffer error case - didn't get max vocab id");
	}

	dg_freeallbuffers(&BHarrayhead);

	dg_clearerrors(&BHarrayhead);
#endif
	// success case
	dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead); 

	vocabid = dg_newwordlist(&BHarrayhead, 0);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - create new vocabulary dg_success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    // should only be root created so far in the wordlist hlist
	if (vocabid != dg_defaulthlistelements)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - create new vocabulary dg_success case - got wrong vocab id, expected default number got ");
        dg_writestdoutuinttodec(&BHarrayhead, vocabid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    // parent of this element should be root

	dg_clearerrors(&BHarrayhead);

	// success case 2 w/ error already

	BHarrayhead.errorcount = 1;

	vocabid = dg_newwordlist(&BHarrayhead, 0);

	if (dg_geterrorcount(&BHarrayhead) != 1)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - create new vocabulary dg_success case 2 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (vocabid != dg_defaulthlistelements + 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newwordlist - create new vocabulary dg_success case 2 - got wrong vocab id, got ");
        dg_writestdoutuinttodec(&BHarrayhead, vocabid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    // parent of this element should be root

	dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_newword()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;

	const char* pError = NULL;
    

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newword\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

    // do not need to make a wordlist because new word is not linked into a wordlist
      // and is parentless
    
	definition = dg_newword (
        &BHarrayhead,
        1, // compilebufid, 
        2, // compilebufoffset,
        3, // databufid,
        4, // databufoffset,
        DG_CORE_BUFFERID, // namebufid,
        (UINT64)"testword", // nameoffset,
        8); /// namelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newword - create new vocabulary dg_success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    // only root element 0 existed before call to dg_newword
    
    if (definition != dg_defaulthlistelements)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newword - create new vocabulary dg_success case - got wrong vocab id, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
    
    // need to make sure word went into correct wordlist

	dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_getpdefinition()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 word1;
    UINT64 word2;

	Definitionheader* pdefinition = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getpdefinition\n");

	// success case
	dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	word1 = dg_newword(&BHarrayhead, 1, 2, 3, 4, DG_CORE_BUFFERID, (UINT64)"yobeu", 5); // 0

	word2 = dg_newword(&BHarrayhead, 7, 8, 9, 0xA, DG_CORE_BUFFERID, (UINT64)"th3", 3); // 1

	pdefinition = dg_getpdefinition(&BHarrayhead, word1);

	if (pdefinition->compileroutinebuf != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL testdg_getpdefinition dg_success case - got wrong compile buf for definition 0\n");
	}

	pdefinition = dg_getpdefinition(&BHarrayhead, word2);

	if (pdefinition->databuf != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL testdg_getpdefinition dg_success case - got wrong data buf for definition 1\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_linkdefinition()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;

	const char* pError = NULL;
    
    UINT64 word1;
    UINT64 word2;
    UINT64 wordlist1;
    UINT64 wordlist2;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_linkdefinition\n");

	// testing error getting pointer to word list header array 
	dg_initerrors(&BHarrayhead, 1000, &pError);

	dg_linkdefinition(&BHarrayhead, 0, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_linkdefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_linkdefinition error getting pointer to word list header array case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_changehlistelementparentname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_linkdefinition error getting pointer to word list header array case - got wrong error 1 below top\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	//testing word list id out of range case
	

	//testing error getting pdefinition

	//testing dg_success case
	dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	wordlist1 = dg_newwordlist(&BHarrayhead, 0); // 1
	wordlist2 = dg_newwordlist(&BHarrayhead, 0); // 2

	word1 = dg_newword(&BHarrayhead, 5, 6, 7, 8, DG_CORE_BUFFERID, (UINT64)"tweety", 6); // 3
	word2 = dg_newword(&BHarrayhead, 55, 66, 77, 88, DG_CORE_BUFFERID, (UINT64)"sylvester", 9); // 4

	dg_linkdefinition(&BHarrayhead, wordlist2, word1);
	dg_linkdefinition(&BHarrayhead, wordlist2, word2);

	definition = dg_getlatestdefinition(&BHarrayhead, wordlist2);

	if (definition != word2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linkdefinition dg_success case - expected latest of word list 2 to be 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_linkdefinition dg_success case - got an error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead,(unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	definition = dg_getnextdefinition(&BHarrayhead, word2);

	if (definition != word1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_linkdefinition dg_success case - expected next of def 2 to be 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	definition = dg_getnextdefinition(&BHarrayhead, word1);

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_linkdefinition dg_success case - expected next of def 3 to be endofvocabulary, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_createsubthreaddef()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_createsubthreaddef\n");
#ifndef DGLU_NO_DIAPER
	// error getting current compile buffer id
	dg_initerrors(&BHarrayhead, 1000, &pError);

	definition = dg_createsubthreaddef(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createsubthreaddefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef get current compile buffer id error - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef get current compile buffer id error - got wrong error 1 below top\n");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef get current compile buffer id error - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// test error getting current compile buffer length
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, 2398);

	definition = dg_createsubthreaddef(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createsubthreaddefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef get current compile buffer length error - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferlengthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef get current compile buffer length error - got wrong error 1 below top");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef get current compile buffer length error - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// test error creating new definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	definition = dg_createsubthreaddef(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createsubthreaddefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef error creating new definition - got wrong error on top\n" );
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_newwordcopynamename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef error creating new definition - got wrong error 1 below top\n" );
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef error creating new definition - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
#endif
	// dg_success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	definition = dg_createsubthreaddef(&BHarrayhead, (unsigned char*)"mememe", 6);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef dg_success case - got an error \n" );
	}

	if (definition != dg_defaulthlistelements)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef dg_success case - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// dg_success case 2

	definition = dg_createsubthreaddef(&BHarrayhead, (unsigned char*)"youyouyou", 9); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef dg_success case 2 - got an error \n" );
	}

	if (definition != dg_defaulthlistelements + 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createsubthreaddef dg_success case 2 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_createvariabledef()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;
	UINT64 vocabid = 0;

	const char* pError = NULL;

	unsigned char* pbuffer = NULL;
	UINT64* plength = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_createvariabledef\n");
#ifndef DGLU_NO_DIAPER
	// error getting current compile buffer id
	dg_initerrors(&BHarrayhead, 1000, &pError);

	definition = dg_createvariabledef(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createvariabledefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef get current compile buffer id error - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef get current compile buffer id error - got wrong error 1 below top\n");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef get current compile buffer id error - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// test error getting current compile buffer length
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentvariablebuffer, 2398);

	definition = dg_createvariabledef(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createvariabledefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef get current compile buffer length error - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferlengthname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef get current compile buffer length error - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! creatvariabledef get current compile buffer length error - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// test error getting current compile word list id
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	*plength = currentcompilewordlist; 
	 // since current compile buffer id is before current compile wordlist, 
	 // compile buffer id will still be ok but word list id won't

	definition = dg_createvariabledef(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createvariabledefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef get current compile word list error - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef get current compile word list error - got wrong error 1 below top\n");	
    }

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! creatvariabledef get current compile word list error - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// test error creating new definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	definition = dg_createvariabledef(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createvariabledefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef error creating new definition - got wrong error on top\n" );
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_newwordcopynamename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef error creating new definition - got wrong error 1 below top\n" );
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef error creating new definition - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// test error linking new definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, 9384);

	definition = dg_createvariabledef(&BHarrayhead, (unsigned char*)"hoho", 4);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createvariabledefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef error linking new definition - got wrong error on top\n" );
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_linkdefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef error linking new definition - got wrong error 1 below top\n" );
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef error linking new definition - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
#endif

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +1 0 based

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid);

	definition = dg_createvariabledef(&BHarrayhead, (unsigned char*)"mememe", 6); // default +2 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef dg_success case - got an error \n" );
	}

	if (definition != dg_defaulthlistelements + 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef dg_success case - got wrong word id, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// success case 2
	definition = dg_createvariabledef(&BHarrayhead, (unsigned char*)"youyouyou", 9); // default +3 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef dg_success case 2 - got an error \n" );
	}

	if (definition != dg_defaulthlistelements + 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createvariabledef dg_success case 2 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_createconstantdef()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;
	UINT64 vocabid = 0;

	const char* pError = NULL;

	unsigned char* pbuffer = NULL;
	UINT64* plength = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_createconstantdef\n");

	// test error getting current compile word list id
	dg_initbuffers(&BHarrayhead);

	pbuffer = dg_getpbuffer(&BHarrayhead, DG_DATASPACE_BUFFERID, &plength);

	*plength = currentcompilewordlist; 

	definition = dg_createconstantdef(&BHarrayhead, 0, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createconstantdefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef get current compile word list error - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef get current compile word list error - got wrong error 1 below top");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! creatconstantdef get current compile word list error - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// test error creating new definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);

	definition = dg_createconstantdef(&BHarrayhead, 5, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createconstantdefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef error creating new definition - got wrong error on top\n" );
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_newwordcopynamename)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef error creating new definition - got wrong error 1 below top\n" );
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef error creating new definition - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// test error linking new definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, 9384);

	definition = dg_createconstantdef(&BHarrayhead, 6, (unsigned char*)"hoho", 4);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_createconstantdefname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef error linking new definition - got wrong error on top\n" );
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_linkdefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef error linking new definition - got wrong error 1 below top\n" );
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef error linking new definition - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// dg_success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +1 0 based

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid);

	definition = dg_createconstantdef(&BHarrayhead, 7, (unsigned char*)"mememe", 6); // default +2 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef dg_success case - got an error \n" );
	}

	if (definition != dg_defaulthlistelements + 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef dg_success case - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// dg_success case 2
	definition = dg_createconstantdef(&BHarrayhead, 8, (unsigned char*)"youyouyou", 9); // default +3 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef dg_success case 2 - got an error \n" );
	}

	if (definition != dg_defaulthlistelements + 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createconstantdef dg_success case 2 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_getlatestdefinition()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;
	UINT64 vocabid = 0;

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getlatestdefinition\n");

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +1 0 based
	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +2 0 based
	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +3 0 based - to check indexing

	definition = dg_getlatestdefinition(&BHarrayhead, vocabid);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition success case 1 - got an error");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition success case 1 - got wrong definition\n");
	}

	dg_clearerrors(&BHarrayhead);

	// success case 2
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"hey", 3); // default + 4 0 based

	if (definition != dg_defaulthlistelements + 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition success case 2 - got wrong word id, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	definition = dg_getlatestdefinition(&BHarrayhead, vocabid);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition success case 2 - got an error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != dg_defaulthlistelements + 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition success case 2 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// dg_success case 3
	definition = dg_createconstantdef(&BHarrayhead, 39874, (unsigned char*)"lala", 4); // default +5 0 based

	if (definition != dg_defaulthlistelements + 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition dg_success case 3 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

	}

	definition = dg_getlatestdefinition(&BHarrayhead, vocabid); // default +5 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition dg_success case 3 - got an error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != dg_defaulthlistelements + 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getlatestdefinition dg_success case 3 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}



void testdg_getnextdefinition()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

//	Bufferhandle* pBH = NULL;

	UINT64 definition = 0;
	UINT64 vocabid = 0;

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getnextdefinition\n");

	// testing dg_getpdefinition error
	dg_initerrors(&BHarrayhead, 1000, &pError);

	definition = dg_getnextdefinition(&BHarrayhead, 1289);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getnextdefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition dg_getpdefinition error - got wrong error on top\n" );
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_gethlistprevioussiblingname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition dg_getpdefinition error - got wrong error 1 below top\n" );
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition dg_getpdefinition error - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// need to test circular case

	// testing success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +1 0 based 
	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +2 0 based
	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +3 0 based - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"hey", 3); // default +4 0 based
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // default +5 0 based
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // default +6 0 based

	definition = dg_getlatestdefinition(&BHarrayhead, vocabid); // default +6 0 based

	definition = dg_getnextdefinition(&BHarrayhead, definition); // default +5 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition success case 1 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != dg_defaulthlistelements + 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition success case 1 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// testing success case 2
	definition = dg_getnextdefinition(&BHarrayhead, definition); // default +4 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition success case 2 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != dg_defaulthlistelements + 3)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition success case 2 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// testing success case 3
	definition = dg_getnextdefinition(&BHarrayhead, definition);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
        pError = dg_poperror(&BHarrayhead);
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition success case 3 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != DG_ENDOFWORDLIST) // end of list
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition success case 3 - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	dg_clearerrors(&BHarrayhead);

	// testing get link of DG_ENDOFWORDLIST case
	definition = dg_getnextdefinition(&BHarrayhead, DG_ENDOFWORDLIST);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition of endofvocabulary case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getnextdefinition of endofvocabulary case - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_executedefinition()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	Bufferhandle* pBH = NULL;

	UINT64 definition = 0;
	UINT64 vocabid = 0;

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_executedefinition\n");

	// dg_getpdefinition error
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_executedefinition(&BHarrayhead, 38); // definition 38 doesn't exist yet so this is an error

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_executedefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition dg_getpdefinition case - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpdefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition dg_getpdefinition case - got wrong error 1 below top");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// error pushing data offset
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // 0 
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 1
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 2 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"hey", 3); // 0
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 1
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // 2

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_DATASTACK_BUFFERID] );

	pBH->nextunusedbyte = 0;
	pBH->size = 0;
	pBH->maxsize = 0;
	pBH->growby = 0;

	dg_executedefinition(&BHarrayhead, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_executedefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition push data offset error case - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition push data offset error case - got wrong error 1 below top");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// error pushing data buf
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // 0 
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 1
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 2 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"hey", 3); // 0
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 1
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // 2

	pBH = &( ((Bufferhandle*)(BHarrayhead.pbuf))[DG_DATASTACK_BUFFERID] );

	pBH->nextunusedbyte = 0;
	pBH->size    = sizeof (UINT64);
	pBH->maxsize = sizeof (UINT64);
	pBH->growby  = sizeof (UINT64);

	dg_executedefinition(&BHarrayhead, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_executedefinitionname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition push data buf case - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_pushbufferuint64name)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition push data buf case - got wrong error 1 below top");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// error in calling routines
	//dg_initbuffers(&BHarrayhead);

	//dg_initvariables(&BHarrayhead);

	//vocabid = dg_newwordlist(&BHarrayhead); // 0 
	//vocabid = dg_newwordlist(&BHarrayhead); // 1
	//vocabid = dg_newwordlist(&BHarrayhead); // 2 - to check indexing

	//dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	//definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"hey", 3); // 0
	//definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 1
	//definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // 2

	//pdefinition = dg_getpdefinition(&BHarrayhead, 0);

	//pdefinition->compileroutinebuf = 88; // invalid buffer

	//dg_executedefinition(&BHarrayhead, 0);

	//pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_executedefinitiondg_callbuffererror)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition error in called routines case - got wrong error");
	//}

	//dg_freeallbuffers(&BHarrayhead);

	//dg_clearerrors(&BHarrayhead);

	// dg_success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_forthleftbracket(&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // 0 
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 1
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 2 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"hey", 3); // 0
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 1
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // 2

	dg_executedefinition(&BHarrayhead, 0);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_executedefinition dg_success case - got an error\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}



void testdg_finddefinwordlist ()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;
	UINT64 vocabid = 0;
    UINT64 foundword;
    
    UINT64 wordlist1;
    UINT64 wordlist2;
    UINT64 wordlist3;

	const char* pError = (const char*)badbufferhandle;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_finddefinwordlist\n");

	// namelength = 0 case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	definition = dg_finddefinwordlist(&BHarrayhead, 0, (unsigned char*)badbufferhandle, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_finddefinwordlistname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab name length 0 case - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_emptystringerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab name length 0 case - got wrong error 1 below top");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab name length 0 case - got wrong definition\n");

	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// error getting latest definition
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    // dg_inithlists (&BHarrayhead);

	definition = dg_finddefinwordlist(&BHarrayhead, 0, (unsigned char*)badbufferhandle, 5); // no vocabularies yet

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_finddefinwordlistname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab get latest definition error case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_findsortedhlistchildname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab get latest definition error case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab get latest definition error case - got wrong definition\n");

	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// error getting pointer to definition case

	// bad memory at pname case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // 0 
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 1
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 2 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 0
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 1
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // 2
	
	definition = dg_finddefinwordlist(&BHarrayhead, vocabid, (unsigned char*)badbufferhandle, 5); 

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_finddefinwordlistname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab bad memory case - got wrong error on top\n");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_findsortedhlistchildname)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab bad memory case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab bad memory case - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);


	// get next definition error case
    //  changed definition name format, need to update this test
	//dg_initbuffers(&BHarrayhead);

	//dg_initvariables(&BHarrayhead);

	//vocabid = dg_newwordlist(&BHarrayhead); // 0 
	//vocabid = dg_newwordlist(&BHarrayhead); // 1
	//vocabid = dg_newwordlist(&BHarrayhead); // 2 - to check indexing

	//dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	//definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 0
	//definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 1
	//definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // 2

	//dg_popbufferuint64(&BHarrayhead, DG_DEFINITION_BUFFERID);

	//definition = dg_finddefinwordlist(&BHarrayhead, vocabid, (unsigned char*)"blabl", 5); 

	//pError = dg_poperror(&BHarrayhead);

	//if (pError != dg_finddefinwordlistdg_getnextdefinitionerror)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab get next definition error case - got wrong error, got ");
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	//}

	//if (definition != DG_ENDOFWORDLIST)
	//{
	//	dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab get next definition error case - got wrong definition\n");
	//}

	//dg_freeallbuffers(&BHarrayhead);

	//dg_clearerrors(&BHarrayhead);

	// not found success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // 1 
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 2
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 3 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 4
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 5
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"ho", 2); // 6

	definition = dg_finddefinwordlist(&BHarrayhead, vocabid, (unsigned char*)"blabl", 5); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab not found success case - got an error \n");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab not found success case - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// found success case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // 1
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 2
	vocabid = dg_newwordlist(&BHarrayhead, 0); // 3 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid); // setting current compile word list

	foundword = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 4
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 5
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"hoybe", 5); // 6

	definition = dg_finddefinwordlist(&BHarrayhead, vocabid, (unsigned char*)"heybe", 5); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab found success case - got an error \n");
	}

	if (definition != foundword)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab found success case - got wrong definition\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
    
    // found success case 2
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	wordlist1 = dg_newwordlist(&BHarrayhead, 0); // 1
	wordlist2 = dg_newwordlist(&BHarrayhead, 0); // 2
	wordlist3 = dg_newwordlist(&BHarrayhead, 0); // 3 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist2); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 4
	foundword = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 5
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"hoybe", 5); // 6

	definition = dg_finddefinwordlist(&BHarrayhead, wordlist2, (unsigned char*)"hi", 2); 

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab found success case 2 - got an error \n");
	}

	if (definition != foundword)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinvocab found success case 2 - got wrong definition, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, foundword);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got, ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_findefinsearchorder()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;
    
    UINT64 wordlist1;
    UINT64 wordlist2;
    UINT64 wordlist3;
    
    UINT64 foundword;

	const char* pError = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_finddefinsearchorder\n");

	// namelength = 0 case
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	definition = dg_finddefinsearchorder(&BHarrayhead, NULL, 0);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_finddefinsearchordername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinsearchorder name length 0 case - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_emptystringerror)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinsearchorder name length 0 case - got wrong error 1 below top");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinsearchorder name length 0 case - got wrong definition\n");

	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
#ifndef DGLU_NO_DIAPER
	// error getting pointer to search order stack
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	dg_freebuffer(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);

	definition = dg_finddefinsearchorder(&BHarrayhead, NULL, 5);

	pError = dg_poperror(&BHarrayhead);

	if (pError != dg_finddefinsearchordername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinsearchorder error getting pointer to search order buffer case - got wrong error on top");
	}

    pError = dg_poperror(&BHarrayhead);

	if (pError != dg_getpbuffername)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinsearchorder error getting pointer to search order buffer case - got wrong error 1 below top");
	}

	if (definition != DG_ENDOFWORDLIST)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! findefinsearchorder error getting pointer to search order buffer case - got wrong definition\n");

	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
#endif
	// error searching a word list case

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	wordlist1 = dg_newwordlist(&BHarrayhead, 0); // 1 
    
	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist1); // setting current compile word list

	foundword = dg_createconstantdef(&BHarrayhead, 451, (unsigned char*)"heybea", 6); // 2
    
    definition = dg_createconstantdef(&BHarrayhead, 661, (unsigned char*)"hia", 3); // 3
    
    definition = dg_createconstantdef(&BHarrayhead, 7771, (unsigned char*)"hoybea", 6); // 4

	wordlist2 = dg_newwordlist(&BHarrayhead, 0); // 5

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist2); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 452, (unsigned char*)"heybeb", 6); // 6
	definition = dg_createconstantdef(&BHarrayhead, 662, (unsigned char*)"hib", 3); // 7
	definition = dg_createconstantdef(&BHarrayhead, 7772, (unsigned char*)"hoybeb", 6); // 8

	wordlist3 = dg_newwordlist(&BHarrayhead, 0); // 9 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist3); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 10
	definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 11
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"hoybe", 5); // 12

	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist2);
	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist3);

	definition = dg_finddefinsearchorder(&BHarrayhead, (unsigned char*)"heybea", 6);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_success case 1 - got an error\n");
	}

	if (definition != foundword)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_success case 1 - got wrong definition. Got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected, ");
        dg_writestdoutuinttodec(&BHarrayhead, foundword);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);

	// dg_success case 2
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	wordlist1 = dg_newwordlist(&BHarrayhead, 0); // 1 

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist1); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 451, (unsigned char*)"heybea", 6); // 2
	definition = dg_createconstantdef(&BHarrayhead, 661, (unsigned char*)"hia", 3); // 3
	definition = dg_createconstantdef(&BHarrayhead, 7771, (unsigned char*)"hoybea", 6); // 4

	wordlist2 = dg_newwordlist(&BHarrayhead, 0); // 5

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist2); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 452, (unsigned char*)"heybeb", 6); // 6
	definition = dg_createconstantdef(&BHarrayhead, 662, (unsigned char*)"hib", 3); // 7
	definition = dg_createconstantdef(&BHarrayhead, 7772, (unsigned char*)"hoybeb", 6); // 8

	wordlist3 = dg_newwordlist(&BHarrayhead, 0); // 9 - to check indexing

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist3); // setting current compile word list

	definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 10
	foundword = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 11
	definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"hoybe", 5); // 12

	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist2);
	dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist3);

	definition = dg_finddefinsearchorder(&BHarrayhead, (unsigned char*)"hi", 2);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_success case 2 - got an error\n");
	}

	if (definition != foundword)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_success case 2 - got wrong definition. Got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" expected, ");
        dg_writestdoutuinttodec(&BHarrayhead, foundword);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}



struct Premadeword mypresortedtestwords[] = {

    { (const char*)"!", 1, 
      (UINT64)DG_CORE_BUFFERID, (UINT64)&dg_forthdocompiletypesubroutine, 
      (UINT64)DG_CORE_BUFFERID, (UINT64)&dg_forthstore},

    { (const char*)"#", 1,
      (UINT64)DG_CORE_BUFFERID, (UINT64)&dg_forthdocompiletypesubroutine,
      (UINT64)DG_CORE_BUFFERID, (UINT64)&dg_forthnumbersign}
};

    
void testdg_newpresortedwordlist()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

    UINT64 wordlist1;
    
    unsigned char* pname;
    UINT64 namelength;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newpresortedwordlist\n");

	// success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);
    
    wordlist1 = dg_newpresortedwordlist (
        &BHarrayhead,
        &(mypresortedtestwords[0]), // struct Premadeword *pmypresortedwordlist,
        2); // UINT64 mypresortedwordlistlength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newpresortedwordlist dg_success case 1 - got an error creating new presorted wordlist, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pname = dg_getshlistelementnom (
        &BHarrayhead,
        0, // hlistheaderid,
        wordlist1 + 1, // elementid,
        &namelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newpresortedwordlist dg_success case 1 - got an error getting s of parent element's name\n");
	}
    
    if (namelength != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newpresortedwordlist dg_success case 1 - 1st child's name length is wrong\n");
    }
    
    if (pname[0] != '!')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newpresortedwordlist dg_success case 1 - 1st child's name is wrong\n");
    }
    
    pname = dg_getshlistelementnom (
        &BHarrayhead,
        0, // hlistheaderid,
        wordlist1 + 2, // elementid,
        &namelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newpresortedwordlist dg_success case 1 - got an error getting s of parent element's name\n");
	}
    
    if (namelength != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newpresortedwordlist dg_success case 1 - 1st child's name length is wrong\n");
    }
    
    if (pname[0] != '#')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_newpresortedwordlist dg_success case 1 - 1st child's name is wrong\n");
    }

    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}

void testdg_copyandrenamewordid()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 oldwordid = 0;
    UINT64 newwordid = 0;

    const char* pError = NULL;
    Definitionheader* pdefinition;
    

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_copyandrenamewordid\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

    // do not need to make a wordlist because new word is not linked into a wordlist
      // and is parentless
    
    oldwordid = dg_newword (
        &BHarrayhead,
        1, // compilebufid, 
        2, // compilebufoffset,
        3, // databufid,
        4, // databufoffset,
        DG_CORE_BUFFERID, // namebufid,
        (UINT64)"testword", // nameoffset,
        8); /// namelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got an error making old word, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // only root element 0 existed before call to dg_newword
    
    if (oldwordid != dg_defaulthlistelements)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got wrong old word id, got ");
        dg_writestdoutuinttodec(&BHarrayhead, oldwordid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    newwordid = dg_copyandrenamewordid (
        &BHarrayhead,
        oldwordid,
        (unsigned char*)"mynewname",
        9);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got an error doing dg_copyandrenamewordid, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ((newwordid == oldwordid) ||
        (newwordid == DG_ENDOFWORDLIST))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got wrong new word id, got ");
        dg_writestdoutuinttodec(&BHarrayhead, newwordid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pdefinition = dg_getpdefinition(
        &BHarrayhead,
        newwordid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got an error doing dg_getpdefinition, got ");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"newwordid = ");
        dg_writestdoutuinttodec(&BHarrayhead, newwordid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pdefinition->compileroutinebuf != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got wrong new compileroutine buffer, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->compileroutinebuf);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdefinition->compileroutineoffset != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got wrong new compileroutine offset, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->compileroutineoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdefinition->databuf != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got wrong new data buf, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->databuf);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdefinition->dataoffset != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_copyandrenamewordid - success case - got wrong new data offset, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->dataoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_findcopyandrenameword()
{
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    UINT64 oldwordid = 0;
    UINT64 newwordid = 0;
    UINT64 wordlist1;
    UINT64 wordlist2;
    UINT64 wordlist3;
    UINT64 foundword;
    UINT64 definition;

    const char* pError = NULL;
    Definitionheader* pdefinition;
    
    unsigned char* pname;
    UINT64 namelength;
    

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_findcopyandrenameword\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

    wordlist1 = dg_newwordlist(&BHarrayhead, 0); // 1 
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist1); // setting current compile word list

    foundword = dg_createconstantdef(&BHarrayhead, 451, (unsigned char*)"heybea", 6); // 2
    
    definition = dg_createconstantdef(&BHarrayhead, 661, (unsigned char*)"hia", 3); // 3
    
    definition = dg_createconstantdef(&BHarrayhead, 7771, (unsigned char*)"hoybea", 6); // 4

    wordlist2 = dg_newwordlist(&BHarrayhead, 0); // 5

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist2); // setting current compile word list

    definition = dg_createconstantdef(&BHarrayhead, 452, (unsigned char*)"heybeb", 6); // 6
    definition = dg_createconstantdef(&BHarrayhead, 662, (unsigned char*)"hib", 3); // 7
    definition = dg_createconstantdef(&BHarrayhead, 7772, (unsigned char*)"hoybeb", 6); // 8

    wordlist3 = dg_newwordlist(&BHarrayhead, 0); // 9 - to check indexing

    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, wordlist3); // setting current compile word list

    definition = dg_createconstantdef(&BHarrayhead, 45, (unsigned char*)"heybe", 5); // 10
    definition = dg_createconstantdef(&BHarrayhead, 66, (unsigned char*)"hi", 2); // 11
    definition = dg_createconstantdef(&BHarrayhead, 777, (unsigned char*)"hoybe", 5); // 12

    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist1);
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist2);
    dg_pushbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, wordlist3);
    
    oldwordid = dg_newword (
        &BHarrayhead,
        1, // compilebufid, 
        2, // compilebufoffset,
        3, // databufid,
        4, // databufoffset,
        DG_CORE_BUFFERID, // namebufid,
        (UINT64)"testword", // nameoffset,
        8); /// namelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got an error making old word, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_linkdefinition(
        &BHarrayhead,
        wordlist1,
        oldwordid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got an error linking old word, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // only root element 0 existed before call to dg_newword
    
    newwordid = dg_findcopyandrenameword (
        &BHarrayhead,
        (unsigned char*)"testword",
        8,
        (unsigned char*)"mynewname",
        9);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got an error doing dg_findcopyandrenameword, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ((newwordid == oldwordid) ||
        (newwordid == DG_ENDOFWORDLIST))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got wrong new word id, got ");
        dg_writestdoutuinttodec(&BHarrayhead, newwordid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pdefinition = dg_getpdefinition(
        &BHarrayhead,
        newwordid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got an error doing dg_getpdefinition, got ");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"newwordid = ");
        dg_writestdoutuinttodec(&BHarrayhead, newwordid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (pdefinition->compileroutinebuf != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got wrong new compileroutine buffer, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->compileroutinebuf);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdefinition->compileroutineoffset != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got wrong new compileroutine offset, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->compileroutineoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdefinition->databuf != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got wrong new data buf, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->databuf);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pdefinition->dataoffset != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got wrong new data offset, got ");
        dg_writestdoutuinttodec(&BHarrayhead, pdefinition->dataoffset);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pname = dg_getshlistelementnom (
        &BHarrayhead,
        DG_WORDLISTS_HLISTID,
        newwordid,
        &namelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got an error doing dg_getshlistelementnom, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (namelength != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got wrong new name namelength");
        dg_writestdoutuinttodec(&BHarrayhead, namelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pname[0] != 'm')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_findcopyandrenameword - success case - got wrong new name first letter, got ");
        dg_writestdout(
            &BHarrayhead,
            (unsigned char*)pname,
            namelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_createbrackettoorderconstantdef()
{
	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	UINT64 definition = 0;
	UINT64 vocabid = 0;
    UINT64 x;

	const char* pError = NULL;

	unsigned char* pbuffer = NULL;
	UINT64* plength = NULL;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_createbrackettoorderconstantdef\n");

	// dg_success case 1
	dg_initbuffers(&BHarrayhead);

	dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

	vocabid = dg_newwordlist(&BHarrayhead, 0); // default +1 0 based

	dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, vocabid);

	definition = dg_createbrackettoorderconstantdef(
        &BHarrayhead, 
        0x123, 
        (unsigned char*)"mememe", 
        6); // default +2 0 based

	if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createbrackettoorderconstantdef dg_success case - got an error doing the createbrackettoorderconstantdef\n" );
	}

	if (definition != dg_defaulthlistelements + 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createbrackettoorderconstantdef dg_success case - got wrong definition, got ");
        dg_writestdoutuinttodec(&BHarrayhead, definition);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
	}
 
    dg_executedefinition (
        &BHarrayhead,
        definition);   
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createbrackettoorderconstantdef dg_success case - got an error executing the new definition\n" );
	}
 
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_SEARCHORDERSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createbrackettoorderconstantdef dg_success case - got an error popping top value from search order stack\n" );
	}
 
    if (x != 0x123)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_createbrackettoorderconstantdef dg_success case - got wrong 1st wordlist from dg_currentfrom, expected 0x123, got " );
        dg_writestdoutuint64tohex(
            &BHarrayhead,
            x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n" );
    }
	
    dg_clearerrors(&BHarrayhead);
	dg_freeallbuffers(&BHarrayhead);
}

