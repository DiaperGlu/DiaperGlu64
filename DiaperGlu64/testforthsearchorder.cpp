// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.13.
//
//    DiaperGlu v5.13 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.13 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.13; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// February 2, 2025           //
// version 5.13               //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"

void testdg_forthgetcurrent ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    const char* pError;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthgetcurrent\n");
    
    // error getting current compile wordlist id
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent success case - could not initialize buffers\n");
        return;
    }
    
    // variables not initialized
    dg_forthgetcurrent(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthgetcurrentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent error getting current compile wordlist id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthpcurrentcreatewordlistname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent error getting current compile wordlist id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // error pushing to the data stack
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent success case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent success case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_freebuffer(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, 5);
    
    // there is no data stack
    dg_forthgetcurrent(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthgetcurrentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent error getting current compile wordlist id case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent error getting current compile wordlist id case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent success case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent success case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist, 5);
    
    dg_forthgetcurrent(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent success case - got an error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent success case - got wrong value\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthsetcurrent ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    const char* pError;
    
    UINT64 mywordlist;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsetcurrent\n");
    
    // error popping data stack
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent error popping data stack case case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetcurrent error popping data stack case case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    // data stack is empty
    dg_forthsetcurrent(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthsetcurrentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent error popping data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthdatastackbufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent error popping data stack case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // wordlist does not exist case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent wordlist does not exist case - could not initialize buffers\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 5);
    
    // wordlist id is for a wordlist that does not exit
    dg_forthsetcurrent(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthsetcurrentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent wordlist does not exist case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getpdefinitionname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent wordlist does not exist case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // getting an error setting the wordlist id is difficult
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent success case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent success case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    mywordlist = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent success case - could not make a new wordlist\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    
    //dg_initwordlists(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent success case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, mywordlist);
    
    dg_forthsetcurrent(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent success case - got an error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilewordlist);
    
    if (x != mywordlist)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetcurrent success case - got wrong value, expected 1 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthsetorder ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    const char* pError;
    UINT64 searchorderbufferlength;
    
    UINT64 mywordlist1;
    UINT64 mywordlist2;
    UINT64 mywordlist3;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsetorder\n");
    
    // empty data stack case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder empty data stack case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder empty data stack case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    mywordlist1 = dg_newwordlist(&BHarrayhead, 0);
    
    //dg_initwordlists(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder empty data stack case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    searchorderbufferlength = dg_getbufferlength(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);
    
    dg_forthsetorder(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthsetordername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder empty data stack case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder empty data stack case - got wrong error 1 below top, expected underflow got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // search order should be unchanged
    if (dg_getbufferlength(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID) != searchorderbufferlength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder empty data stack case - search order was changed\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    // data stack underflow case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder data stack underflow case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder data stack underflow case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    mywordlist1 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist2 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist3 = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder data stack underflow case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    searchorderbufferlength = dg_getbufferlength(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);
    
    dg_pushdatastack(&BHarrayhead, mywordlist2);
    dg_pushdatastack(&BHarrayhead, mywordlist1);
    dg_pushdatastack(&BHarrayhead, mywordlist3);
    dg_pushdatastack(&BHarrayhead, 4);
    
    dg_forthsetorder(&BHarrayhead);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthsetordername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder data stack underflow case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_datastackunderflowerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder data stack underflow case - got wrong error 1 below top, expected underflow got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // search order should be unchanged
    if (dg_getbufferlength(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID) != searchorderbufferlength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder data stack underflow case - search order was changed\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    mywordlist1 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist2 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist3 = dg_newwordlist(&BHarrayhead, 0);

    
    //dg_initwordlists(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, mywordlist2);
    dg_pushdatastack(&BHarrayhead, mywordlist1);
    dg_pushdatastack(&BHarrayhead, mywordlist3);
    dg_pushdatastack(&BHarrayhead, 3);
    
    dg_forthsetorder(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x =dg_popbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);
    
    if (x != mywordlist3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - top wordlist on search order stack incorrect, expected 2 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x =dg_popbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);

    if (x != mywordlist1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - 1 below top wordlist on search order stack incorrect, expected 0 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x =dg_popbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);

    if (x != mywordlist2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - 2 below top wordlist on search order stack incorrect, expected 1 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success case - wrong number of wordlist ids on search order stack\n");
    }

    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success empty search order case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success empty search order case case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success empty search order case case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    mywordlist1 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist2 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist3 = dg_newwordlist(&BHarrayhead, 0);

    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success empty search order case case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 0);
    
    dg_forthsetorder(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success empty search order case case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success empty search order case case - search order not empty\n");
    }

    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success minimum search order case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success minimum search order case case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success minimum search order case case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    mywordlist1 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist2 = dg_newwordlist(&BHarrayhead, 0);
    mywordlist3 = dg_newwordlist(&BHarrayhead, 0);
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_corewordlistid, mywordlist2);

    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success minimum search order case case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, (UINT64)-1);
    
    dg_forthsetorder(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success minimum search order case case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popbufferuint64(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);
    
    if (x != mywordlist2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success minimum search order case case - search order set to wrong word list id\n");
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_SEARCHORDERSTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsetorder success minimum search order case case - search order not empty\n");
    }

    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    // error pushing to the search order stack is difficult to get... unless I make the search order larger than the buffer
}

/*
void testdg_forthgetorder ()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthgetorder\n");
    
    // success case
    //  assumes dg_forthsetorder has already been tested
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);

    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - could not initialize the wordlist hlist\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }

    dg_initwordlists(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - could not initialize the wordlists\n");
	dg_forthdoterrors(&BHarrayhead);
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 2);
    dg_pushdatastack(&BHarrayhead, 0);
    dg_pushdatastack(&BHarrayhead, 1);
    dg_pushdatastack(&BHarrayhead, 3);
    
    dg_forthsetorder(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - could not set order\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_forthgetorder(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - number of wordlists on top of data stack incorrect\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - wordlist id 1 below top of data stack incorrect\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - wordlist id 2 below top of data stack incorrect\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthgetorder success case - wordlist id 3 below top of data stack incorrect\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
}
*/

void testdg_forthwordlist()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    const char* pError;
    UINT64 wid;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthwordlist\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordlist success case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordlist success case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    wid = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordlist success case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    //wordlistheaderbufferlength = dg_getbufferlength(&BHarrayhead, DG_WORDLISTHEADERARRAY_BUFFERID);
    
    dg_forthwordlist(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordlist success case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    //if (x != (wordlistheaderbufferlength/sizeof(UINT64)) )
    if (x != wid+1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordlist success case - got wrong wordlist id back\n");
    }
    
    /*
    if ((wordlistheaderbufferlength + sizeof(UINT64)) != dg_getbufferlength(&BHarrayhead, DG_WORDLISTHEADERARRAY_BUFFERID) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthwordlist success case - word list header array incorrect\n");
    }
    */
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdefinitions()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    UINT64 wordlist1;
    UINT64 wordlist2;
    UINT64 wordlist3;
    UINT64 wordlist4;

    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthdefinitions\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    wordlist2 = dg_newwordlist(&BHarrayhead, 0);
    wordlist3 = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, wordlist1);
    dg_forthsetcurrent(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, wordlist3);
    dg_pushdatastack(&BHarrayhead, wordlist1);
    dg_pushdatastack(&BHarrayhead, wordlist2);
    dg_pushdatastack(&BHarrayhead, 3);
    
    dg_forthsetorder(&BHarrayhead);
    
    dg_forthdefinitions(&BHarrayhead);
    
    dg_forthgetcurrent(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != wordlist2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success case - got wrong wordlist id, expected wordlist 2 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 2
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success 2 case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success 2 case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    wordlist1 = dg_newwordlist(&BHarrayhead, 0);
    wordlist2 = dg_newwordlist(&BHarrayhead, 0);
    wordlist3 = dg_newwordlist(&BHarrayhead, 0);
    wordlist4 = dg_newwordlist(&BHarrayhead, 0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success 2 case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, wordlist1);
    dg_forthsetcurrent(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, wordlist3);
    dg_pushdatastack(&BHarrayhead, wordlist1);
    dg_pushdatastack(&BHarrayhead, wordlist2);
    dg_pushdatastack(&BHarrayhead, wordlist4);
    dg_pushdatastack(&BHarrayhead, 4);
    
    dg_forthsetorder(&BHarrayhead);
    
    dg_forthdefinitions(&BHarrayhead);
    
    dg_forthgetcurrent(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != wordlist4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthdefinitions success 2 case - got wrong wordlist id, expected wordlist4 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
}

/*
void testdg_forthsearchwordlist()
{
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    UINT64 x;
    UINT64 corewid;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsearchwordlist\n");
    
    // success not found case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success not found case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success not found case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    //dg_initwordlists(&BHarrayhead);
    corewid = dg_newwordlist(&BHarrayhead, 0);
    
    
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success not found case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    corewid = dg_getbufferuint64(&BHarrayhead, DG_DATASTACK_BUFFERID, dg_corewordlistid);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)"zebra");
    dg_pushdatastack(&BHarrayhead, 5);
    dg_pushdatastack(&BHarrayhead, corewid);
    
    dg_forthsearchwordlist(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success not found case - got wrong result\n"); 
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success not found case - data stack not empty after test\n");
    }
            
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success found not immediate case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    dg_initwordlists(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    corewid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_corewordlistid);
    
    dg_pushdatastack(&BHarrayhead, 8);
    dg_pushdatastack(&BHarrayhead, 20);
    dg_pushdatastack(&BHarrayhead, (UINT64)"SWAP");
    dg_pushdatastack(&BHarrayhead, 4);
    dg_pushdatastack(&BHarrayhead, corewid);
    
    dg_forthsearchwordlist(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - got wrong result\n"); 
    }
    
    // execute token for swap
    dg_forthexecute(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - wrong execution token\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - wrong execution token 2\n");
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - data stack not empty after test\n");
    }

    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
    
    
    // success found immediate case
    dg_initbuffers(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found immediate case - could not initialize buffers\n");
        return;
    }
    
    dg_initvariables(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found immediate case - could not initialize variables\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    dg_inithlists (&BHarrayhead);
    
    dg_initwordlists(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found immediate case - could not initialize the wordlists\n");
        dg_freeallbuffers(&BHarrayhead);
        return;
    }
    
    corewid = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_corewordlistid);
    
    dg_forthrightbracket(&BHarrayhead);
    
    dg_pushdatastack(&BHarrayhead, (UINT64)"[");
    dg_pushdatastack(&BHarrayhead, 1);
    dg_pushdatastack(&BHarrayhead, corewid);
    
    //dg_forthdup(&BHarrayhead);
    //dg_forthshowwordlist(&BHarrayhead);
    
    dg_forthsearchwordlist(&BHarrayhead);
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found immediate case - got wrong result. Expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // execute token for right bracket
    dg_forthexecute(&BHarrayhead);
    
    x = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, statevariable);
    
    if (x != (UINT64)dg_stateexecute)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found immediate case - got wrong execute token\n");
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_forthsearchwordlist success found not immediate case - data stack not empty after test\n");
    }

    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
}
*/

