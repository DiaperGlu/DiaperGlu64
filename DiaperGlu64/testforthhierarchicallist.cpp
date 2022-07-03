// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.5.
//
//    DiaperGlu v5.5 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.5 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.5; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// July 2, 2022               //
// version 5.5                //
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
