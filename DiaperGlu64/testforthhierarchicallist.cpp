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


void testdg_forthnewhlist()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 myhlist1, myhlist2;
    
    Hlistheader myhlistheader;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnewhlist\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    dg_forthnewhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlist success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myhlist1 = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlist success case - got error popping 1st hlistid, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthnewhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlist success case - got error making 2nd new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myhlist2 = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlist success case - got error popping 2nd hlistid, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlist2 != myhlist1 + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlist success case - 2nd hlist id not 2 more than 1st.\n");
    }
    
      // just seeing if hlist was in fact created. dg_newhlist is already tested
    dg_gethlistheader(
        &BHarrayhead,
        myhlist1,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlist success case - error getting 1st hlist header, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlist2,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlist success case - error getting 2nd hlist header, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthfreehlist()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 myhlist1;
    
    Hlistheader myhlistheader;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthfreehlist\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    dg_forthnewhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfreehlist success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myhlist1 = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfreehlist success case - got error popping 1st new hlist id, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(&BHarrayhead, myhlist1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfreehlist success case - got error pushing 1st new hlist id, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_forthfreehlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfreehlist success case - got error freehing 1st hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlist1,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfreehlist success case - didn't get error getting header of freed hlist.\n");
    }
    
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthnewhlistelement()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 myhlist1;
    UINT64 myelement1;
    
    unsigned char* pmyname1;
    UINT64 mynamelength1;
    unsigned char* pmyvalue1;
    UINT64 myvaluelength1;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthnewhlistelement\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    dg_forthnewhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myhlist1 = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error popping 1st new hlist id, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(&BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		8,
		(unsigned char*)"myvalue1");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring(&BHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		7,
		(unsigned char*)"myname1");
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(&BHarrayhead, DG_ENDOFLIST);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error pushing parent element id, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(&BHarrayhead, myhlist1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error pushing 1st new hlist id, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthnewhlistelement(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelement1 = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error popping 1st new element id, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_getshlistelement (
        &BHarrayhead,
        myhlist1,
        myelement1,
        &pmyname1,
        &mynamelength1,
        &pmyvalue1,
        &myvaluelength1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthnewhlistelement success case - got error getting s'es of new hlist element1, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthehdot()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 myhlist1;
    UINT64 myparentelement1;
    UINT64 myelement1;
    
    unsigned char* pmyname1;
    UINT64 mynamelength1;
    unsigned char* pmyvalue1;
    UINT64 myvaluelength1;
    
    UINT64 x;
    UINT64 bufferid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthehdot\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myparentelement1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error pushing parent element to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myhlist1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error pushing parent hlist to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    
    x = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child1", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 7;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child2", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 11;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child3", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error making third child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        (unsigned char*)"child2", // psrc
        6); // UINT64 srclength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error pushing test string to new buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error setting the current interpret buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehdot(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - got error doing ehdot, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x !=  7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehdot success case - expected x = 7, got x = ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthehbracketnddot()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 myhlist1;
    UINT64 myparentelement1;
    UINT64 myelement1;
    
    unsigned char* pmyname1;
    UINT64 mynamelength1;
    unsigned char* pmyvalue1;
    UINT64 myvaluelength1;
    
    UINT64 x;
    UINT64 bufferid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthehbracketnddot\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myparentelement1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error pushing parent element to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myhlist1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error pushing parent hlist to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    
    x = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child1", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 7;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child2", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 11;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child3", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error making third child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        (unsigned char*)"child2", // psrc
        6); // UINT64 srclength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error pushing test string to new buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error setting the current interpret buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(
        &BHarrayhead,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error pushing nd = 0 to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehbracketnddot(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - got error doing ehdot, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x !=  7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case - expected x = 7, got x = ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    
    // sucess case 2
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myparentelement1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error pushing parent element to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myhlist1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error pushing parent hlist to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error pushing 1st 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error pushing 2nd 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    
    x = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child1", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 7;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child2", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 11;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child3", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error making third child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        (unsigned char*)"child2", // psrc
        6); // UINT64 srclength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error pushing test string to new buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error setting the current interpret buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(
        &BHarrayhead,
        1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error pushing nd = 0 to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehbracketnddot(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - got error doing ehdot, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x !=  7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 2 - expected x = 7, got x = ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
    
    
    // sucess case 3
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myparentelement1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing parent element to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myhlist1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing parent hlist to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing 1st 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing 2nd 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing 3rd 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing 4th 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    
    x = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child1", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 7;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child2", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 11;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child3", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error making third child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        (unsigned char*)"child2", // psrc
        6); // UINT64 srclength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing test string to new buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error setting the current interpret buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushdatastack(
        &BHarrayhead,
        2);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error pushing nd = 0 to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehbracketnddot(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - got error doing ehdot, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x !=  7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracketnddot success case 3 - expected x = 7, got x = ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthehbracket1ddot()
{
    Bufferhandle BHarrayhead;
    const char* pError;
    
    UINT64 myhlist1;
    UINT64 myparentelement1;
    UINT64 myelement1;
    
    unsigned char* pmyname1;
    UINT64 mynamelength1;
    unsigned char* pmyvalue1;
    UINT64 myvaluelength1;
    
    UINT64 x;
    UINT64 bufferid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthehbracket1ddot\n");
    
    
    // sucess case 2
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error making 1st new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myparentelement1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error pushing parent element to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myhlist1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error pushing parent hlist to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error pushing 1st 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        0);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error pushing 2nd 0 to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    
    x = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child1", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 7;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child2", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = 11;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, 
        (unsigned char*)"child3", // pname,
        6, // namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error making third child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    bufferid = dg_stonewbuffer (
        &BHarrayhead,
        0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        (unsigned char*)"child2", // psrc
        6); // UINT64 srclength);

	if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error pushing test string to new buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentinterpretbuffer,
        bufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error setting the current interpret buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehbracket1ddot(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - got error doing ehdot, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x !=  7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehbracket1ddot success case 2 - expected x = 7, got x = ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthehnewelements()
{
    Bufferhandle BHarrayhead;
    
    UINT64 myhlist1;
    UINT64 myparentelement1;
    UINT64 myelement1;
    
    unsigned char* pmyname1;
    UINT64 mynamelength1;
    unsigned char* pmyvalue1;
    UINT64 myvaluelength1;

    UINT64 stringstackdepth;

    const char* pError;
    UINT64 x;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthehnewelements\n");
    
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error making new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myparentelement1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error pushing parent element to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID,
        myhlist1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error pushing parent hlist to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"Yi",
        2);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error pushing first string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"name",
        4);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error pushing second string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"Spot!",
        5);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error pushing third string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"cat",
        3);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error pushing fourth string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_pushdatastack(&BHarrayhead, 2);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error pushing to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehnewelements(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected data stack depth = 0, got data stack depth = ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    stringstackdepth = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    if (stringstackdepth != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected stringstackdepth = 0, got stringstackdepth = ");
        dg_writestdoutuinttodec(&BHarrayhead, stringstackdepth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_getshlistelement (
        &BHarrayhead,
        myhlist1,
        2, // elementid,
        &pmyname1,
        &mynamelength1,
        &pmyvalue1,
        &myvaluelength1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error getting pointer to first child element's strings, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (myvaluelength1 != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value 0 length = 2, got value 0 length = ");
        dg_writestdoutuinttodec(&BHarrayhead, myvaluelength1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (mynamelength1 != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name 0 length = 4, got name 0 length = ");
        dg_writestdoutuinttodec(&BHarrayhead, mynamelength1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pmyname1[0] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name0[0] = 'n', got name0[0] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyname1[0],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyname1[1] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name0[1] = 'a', got name0[1] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyname1[1],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyname1[2] != 'm')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name0[2] = 'm', got name0[2] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyname1[2],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyname1[3] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name0[3] = 'e', got name0[3] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyname1[3],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[0] != 'Y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value0[0] = 'Y', got value0[0] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[0],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[1] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value0[1] = 'i', got value0[1] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[1],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    dg_getshlistelement (
        &BHarrayhead,
        myhlist1,
        1, // elementid,
        &pmyname1,
        &mynamelength1,
        &pmyvalue1,
        &myvaluelength1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error getting pointer to second child element's strings, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (myvaluelength1 != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value 1 length = 5, got value 1 length = ");
        dg_writestdoutuinttodec(&BHarrayhead, myvaluelength1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (mynamelength1 != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name 1 length = 3, got name 0 length = ");
        dg_writestdoutuinttodec(&BHarrayhead, mynamelength1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pmyname1[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name1[0] = 'c', got name1[0] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyname1[0],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyname1[1] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name1[1] = 'a', got name1[1] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyname1[1],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyname1[2] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected name1[2] = 't', got name1[2] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyname1[2],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[0] != 'S')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value1[0] = 'S', got value1[0] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[0],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[1] != 'p')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value1[1] = 'p', got value1[1] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[1],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[2] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value1[2] = 'o', got value1[2] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[2],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[3] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value1[3] = 't', got value1[3] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[3],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[4] != '!')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value1[4] = '!', got value1[4] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[4],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    x = dg_gethlistelementparent (
        &BHarrayhead,
        myhlist1,
        2);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error getting second child element's parent, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected 2nd parent element id = 0, got parent element id = ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_gethlistelementparent (
        &BHarrayhead,
        myhlist1,
        1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - got error getting first child element's parent, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected 1st parent element id = 0, got parent element id = ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthquerynamestrtovaluestr()
{
    Bufferhandle BHarrayhead;
    
    UINT64 myhlist1;
    UINT64 myparentelement1;
    UINT64 myelement1;
    
    unsigned char* pmyvalue1;
    UINT64 myvaluelength1;

    UINT64 stringstackdepth;

    const char* pError;
    UINT64 x;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthquerynamestrtovaluestr\n");
    
    
    // sudcess found case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error making new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"name", // pname,
        4, // namelength,
        (unsigned char*)"Yi", // pvalue,
        2); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"cat", // pname,
        3, // namelength,
        (unsigned char*)"Spot!", // pvalue,
        5); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"name",
        4);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error pushing name string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    dg_pushdatastack(&BHarrayhead, myparentelement1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error pushing elementid to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_pushdatastack(&BHarrayhead, myhlist1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error pushing hlistid to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthquerynamestrtovaluestr(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (x != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - expected data stack depth = 1, got data stack depth = ");
        dg_writestdoutuinttodec(&BHarrayhead, x/sizeof(UINT64));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - expected returned flag = FORTH_TRUE (-1), got data flag = ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    stringstackdepth = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    if (stringstackdepth != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success found case - expected stringstackdepth = 1, got stringstackdepth = ");
        dg_writestdoutuinttodec(&BHarrayhead, stringstackdepth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pmyvalue1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
        &myvaluelength1); // pstringlength)

    if (myvaluelength1 != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value 0 length = 2, got value 0 length = ");
        dg_writestdoutuinttodec(&BHarrayhead, myvaluelength1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pmyvalue1[0] != 'Y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value0[0] = 'Y', got value0[0] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[0],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[1] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehnewelements success case - expected value0[1] = 'i', got value0[1] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[1],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }
       
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


    // success not found case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error making new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"name", // pname,
        4, // namelength,
        (unsigned char*)"Yi", // pvalue,
        2); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"cat", // pname,
        3, // namelength,
        (unsigned char*)"Spot!", // pvalue,
        5); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"willnotfind",
        11);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error pushing name string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    dg_pushdatastack(&BHarrayhead, myparentelement1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error pushing elementid to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_pushdatastack(&BHarrayhead, myhlist1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error pushing hlistid to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthquerynamestrtovaluestr(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (x != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - expected data stack depth = 1, got data stack depth = ");
        dg_writestdoutuinttodec(&BHarrayhead, x/sizeof(UINT64));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - expected returned flag = FORTH_TRUE (-1), got data flag = ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    stringstackdepth = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    if (stringstackdepth != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthquerynamestrtovaluestr success not found case - expected stringstackdepth = 1, got stringstackdepth = ");
        dg_writestdoutuinttodec(&BHarrayhead, stringstackdepth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthehquerynamestrtovaluestr()
{
    Bufferhandle BHarrayhead;
    
    UINT64 myhlist1;
    UINT64 myparentelement1;
    UINT64 myelement1;
    
    unsigned char* pmyvalue1;
    UINT64 myvaluelength1;

    UINT64 stringstackdepth;

    const char* pError;
    UINT64 x;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthehquerynamestrtovaluestr\n");
    
    
    // sudcess found case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error making new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"name", // pname,
        4, // namelength,
        (unsigned char*)"Yi", // pvalue,
        2); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"cat", // pname,
        3, // namelength,
        (unsigned char*)"Spot!", // pvalue,
        5); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"name",
        4);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error pushing name string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_pushbufferuint64( 
        &BHarrayhead,
        DG_EHSTACK_BUFFERID, 
        myparentelement1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error pushing elementid to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

     dg_pushbufferuint64( 
        &BHarrayhead,
        DG_EHSTACK_BUFFERID, 
        myhlist1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error pushing hlistid to eh stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehquerynamestrtovaluestr(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (x != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - expected data stack depth = 1, got data stack depth = ");
        dg_writestdoutuinttodec(&BHarrayhead, x/sizeof(UINT64));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - expected returned flag = FORTH_TRUE (-1), got data flag = ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    stringstackdepth = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    if (stringstackdepth != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success found case - expected stringstackdepth = 1, got stringstackdepth = ");
        dg_writestdoutuinttodec(&BHarrayhead, stringstackdepth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pmyvalue1 = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid,
        &myvaluelength1); // pstringlength)

    if (myvaluelength1 != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success case - expected value 0 length = 2, got value 0 length = ");
        dg_writestdoutuinttodec(&BHarrayhead, myvaluelength1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pmyvalue1[0] != 'Y')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success case - expected value0[0] = 'Y', got value0[0] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[0],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }

    if (pmyvalue1[1] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success case - expected value0[1] = 'i', got value0[1] = '");
        dg_writestdoutraw(
            &BHarrayhead,
            (unsigned char*)&pmyvalue1[1],
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"'\n");
    }
       
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);


    // success not found case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists (&BHarrayhead);
    
    myhlist1 = dg_newhlist (&BHarrayhead);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error making new hlist, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myparentelement1 = dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"parent", // pname,
        6, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error making parent element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"name", // pname,
        4, // namelength,
        (unsigned char*)"Yi", // pvalue,
        2); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error making first child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_newhlistelement (
        &BHarrayhead,
        myhlist1, // hlistid,
        myparentelement1, // parentelementid, 
        (unsigned char*)"cat", // pname,
        3, // namelength,
        (unsigned char*)"Spot!", // pvalue,
        5); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error making second child element, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_stonewstring (
        &BHarrayhead,
        (unsigned char*)"willnotfind",
        11);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error pushing name string to the string stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID, 
        myparentelement1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error pushing elementid to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_pushbufferuint64(
        &BHarrayhead,
        DG_EHSTACK_BUFFERID, 
        myhlist1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error pushing hlistid to data stack, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthehquerynamestrtovaluestr(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - got error doing dg_forthehnewelements, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (x != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - expected data stack depth = 1, got data stack depth = ");
        dg_writestdoutuinttodec(&BHarrayhead, x/sizeof(UINT64));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - expected returned flag = FORTH_TRUE (-1), got data flag = ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
 
    stringstackdepth = dg_getnumberoflstringsonstack(&BHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    if (stringstackdepth != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthehquerynamestrtovaluestr success not found case - expected stringstackdepth = 1, got stringstackdepth = ");
        dg_writestdoutuinttodec(&BHarrayhead, stringstackdepth);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}
