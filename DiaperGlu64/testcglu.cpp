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

void testdg_patchpnewbuffer ()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
     UINT64 myhlistid;
    
    UINT64 myelementid1;
    UINT64 myelementid2;
    UINT64 myelementid3;

    UINT64 mybufferid;
    
    UINT64 myvalue;
    
    unsigned char* mypbuffer;
    UINT64* mypbufferlength;
    UINT64 mybuffersize;
    
    unsigned char* mypbuffer1;
    UINT64* mypbuffer1length;
    
    unsigned char* mypbuffer2;
    UINT64* mypbuffer2length;
    
    UINT64 mydepth;
    
    UINT64 destnamedbuffer;
    
    Hlistheader mydesthlistheader;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_patchpnewbuffer \n");
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists(&BHarrayhead); // need to init the named buffer hlist
    
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer  success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // going to use root as element because patch routine doesn't care what the parent is
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_rootelementname, // pname, // function name
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)&myvalue, // pvalue, // offset in buffer to patch
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error making first new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // buffers are made in sorted name order... could change than
    myvalue = 7;
    mybuffersize = dg_calcnearestpagesize(0x4000);
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)&mybuffersize, // pname,
        sizeof(UINT64), // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error making second new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myvalue = 16;
    mybuffersize = dg_calcnearestpagesize(0x8000);
    
    myelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)&mybuffersize, // pname,
        sizeof(UINT64), // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error making third new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to create a buffer and fill it with a number
    mybufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error making the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to use the buffer
    dg_growbuffer (
        &BHarrayhead,
		mybufferid,
		1000,  // in bytes
		&pError,
		FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error growing the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need pointer to the buffer
    mypbuffer = dg_getpbuffer (
        &BHarrayhead,
        mybufferid,
        &mypbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error getting a pointer to the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_fillwithbyte (
        mypbuffer,
        *mypbufferlength,
        1); // value
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error filling the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // add the buffer to the named buffer list
    destnamedbuffer = dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        (unsigned char*)&"mydestbuffer", // pname,
        12, // namelength,
        (unsigned char*)&mybufferid, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error adding dest buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf,
        destnamedbuffer);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error setting patch dest named buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &mydesthlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // patch the buffer
    dg_forthdepth(&BHarrayhead);
    mydepth = dg_popdatastack(&BHarrayhead);
    
    dg_patchpnewbuffer(
        &BHarrayhead,
        myhlistid,     // id of hlist containing patch new buffer list
        DG_ROOT_ELEMENTID,   // parent element id of the patch new buffer list
        (unsigned char*)"",
        0, //parentvaluelength,
        &mydesthlistheader);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error patching the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_forthdepth(&BHarrayhead);
    if (mydepth != dg_popdatastack(&BHarrayhead))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - data stack corrupted, depth changed during patch\n");
    }
    
    mybufferid = dg_popbufferuint64(&BHarrayhead, DG_LINKNEWBUFFERIDSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error popping buffer id of 2nd new pbuffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mypbuffer2 = dg_getpbuffer (
        &BHarrayhead,
        mybufferid,
        &mypbuffer2length);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error getting a pointer to the second new pbuffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mybufferid = dg_popbufferuint64(&BHarrayhead, DG_LINKNEWBUFFERIDSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error popping buffer id of first new pbuffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mypbuffer1 = dg_getpbuffer (
        &BHarrayhead,
        mybufferid,
        &mypbuffer1length);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - got an error getting a pointer to the first new pbuffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // +7 should be address of first new buffer
    if ( *((UINT64*)(mypbuffer + 7)) != (UINT64)mypbuffer1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - first buffer's address not patched correctly\n");
    }
    
    // +12 should be address of second new buffer
    if ( *((UINT64*)(mypbuffer + 16)) != (UINT64)mypbuffer2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - second buffer's address not patched correctly\n");
    }
    
    if (*(mypbuffer + 6) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - buffer before 1st patch corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypbuffer + 6)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*(mypbuffer + 15) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - buffer between patches corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypbuffer + 11)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*(mypbuffer + 24) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - buffer after patches corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypbuffer + 16)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*mypbuffer1length != 0x4000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - first new buffer's length wrong, expected 0x4000, got ");
        dg_writestdoutuinttodec(&BHarrayhead, *mypbuffer1length);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*mypbuffer2length != 0x8000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchpnewbuffer success case - second new buffer's length wrong, expected 0x8000, got ");
        dg_writestdoutuinttodec(&BHarrayhead, *mypbuffer2length);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_patchaddressusingdlsym ()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    UINT64 myelementid1;
    UINT64 myelementid2;
    UINT64 myelementid3;

    UINT64 myhlibrary;
    UINT64 mybufferid;
    
    UINT64 myvalue;
    
    unsigned char* mypbuffer;
    UINT64* mypbufferlength;
    
    UINT64 mysymbol1;
    UINT64 mysymbol2;
    
    UINT64 mydepth;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_patchaddressusingdlsym \n");
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym  success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // myvalue = 1;
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_rootelementname, // pname, // function name
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)&myvalue, // pvalue, // offset in buffer to patch
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error making first new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myvalue = 7;
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"dg_newhlist", // pname,
        11, // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error making second new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myvalue = 16;
    
    myelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"dg_movebytes", // pname,
        12, // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error making third new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to create a buffer and fill it with a number
    mybufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error making the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to use the buffer
    dg_growbuffer (
        &BHarrayhead,
		mybufferid,
		1000,  // in bytes
		&pError,
		FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error growing the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need pointer to the buffer
    mypbuffer = dg_getpbuffer (
        &BHarrayhead,
        mybufferid,
        &mypbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error getting a pointer to the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_fillwithbyte (
        mypbuffer,
        *mypbufferlength,
        1); // value
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error filling the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // need to open a library
      // push library name to string stack
      // call dg_forthloadlibrarystring
      // pop library handle from data stack
      //   (a wordlist is created and the libhandle is pushed to the open library handle stack
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		DG_DIAPERGLU_LIB_NAME_LENGTH, // length,
        (unsigned char*)DG_DIAPERGLU_LIB_NAME); // psrc
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error pushing the library name to the string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_forthopenlibrarystring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error opening the library, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlibrary = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error popping the library handle from the data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // getting pointers to the functions
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		11, // length,
		(unsigned char*)"dg_newhlist"); // psrc)
    
    dg_pushdatastack(&BHarrayhead, myhlibrary);
    
    dg_forthfindlibrarysymbol(&BHarrayhead);
    
    mysymbol1 = dg_popdatastack(&BHarrayhead);
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		12, // length,
		(unsigned char*)"dg_movebytes"); // psrc)
    
    dg_pushdatastack(&BHarrayhead, myhlibrary);
    
    dg_forthfindlibrarysymbol(&BHarrayhead);
    
    mysymbol2 = dg_popdatastack(&BHarrayhead);
    
    
    // patch the buffer
    dg_forthdepth(&BHarrayhead);
    mydepth = dg_popdatastack(&BHarrayhead);
    
    dg_patchaddressusingdlsym(
        &BHarrayhead,
        myhlistid, // id of hlist containing import list
        myelementid1, // element id of source library name which is parent element id of symbol list
        myhlibrary, // handle of source shared library
        mypbuffer, // address of destination buffer to patch
        *mypbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error patching the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_forthdoterrors(&BHarrayhead);
    }
    
    dg_forthdepth(&BHarrayhead);
    if (mydepth != dg_popdatastack(&BHarrayhead))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - data stack corrupted, depth changed during patch\n");
    }
    
    // +7 should be address of dg_newhlist
    if ( *((UINT64*)(mypbuffer + 7)) != mysymbol1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - first symbol not patched correctly\n");
    }
    
    // +16 should be address of dg_movebytes
    if ( *((UINT64*)(mypbuffer + 16)) != mysymbol2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - second symbol not patched correctly\n");
    }
    
    if (*(mypbuffer + 6) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - buffer before 1st patch corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypbuffer + 6)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*(mypbuffer + 15) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - buffer between patches corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypbuffer + 11)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*(mypbuffer + 24) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - buffer after patches corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypbuffer + 16)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // close the library
    pError = dg_freelibrary(
        myhlibrary,
		dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusingdlsym success case - got an error closing the library, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_patchaddressusinghlist ()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    

    
    UINT64 mydesthlistid;
    
    UINT64 mydestelementid1;
    UINT64 mydestelementid2;
    UINT64 mydestelementid3;
    
    UINT64 mydestbufferid;
    
    UINT64 myvalue;
    
    unsigned char* mypdestbuffer;
    UINT64* mypdestbufferlength;
    
    UINT64 mysrchlistid;
    
    UINT64 mysrcelementid1;
    UINT64 mysrcelementid2;
    UINT64 mysrcelementid3;
    
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_patchaddressusinghlist \n");
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);

    
    mydesthlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist  success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // myvalue = 1;
    
    mydestelementid1 = dg_newhlistelement (
        &BHarrayhead,
        mydesthlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_rootelementname, // pname, // function name
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)&myvalue, // pvalue, // offset in buffer to patch
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error making first new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myvalue = 7;
    
    mydestelementid2 = dg_newhlistelement (
        &BHarrayhead,
        mydesthlistid, // hlistid,
        mydestelementid1, // parentelementid,
        (unsigned char*)"dg_newhlist", // pname,
        11, // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error making second new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myvalue = 16;
    
    mydestelementid3 = dg_newhlistelement (
        &BHarrayhead,
        mydesthlistid, // hlistid,
        mydestelementid1, // parentelementid,
        (unsigned char*)"dg_movebytes", // pname,
        12, // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error making third new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    
    // need to create a buffer and fill it with a number
    mydestbufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error making the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to use the buffer
    dg_growbuffer (
        &BHarrayhead,
		mydestbufferid,
		1000,  // in bytes
		&pError,
		FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error growing the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need pointer to the buffer
    mypdestbuffer = dg_getpbuffer (
        &BHarrayhead,
        mydestbufferid,
        &mypdestbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error getting a pointer to the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_fillwithbyte (
        mypdestbuffer,
        *mypdestbufferlength,
        1); // value
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error filling the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    mysrchlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist  success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // myvalue = 1;
    
    mysrcelementid1 = dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_rootelementname, // pname, // function name
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)&myvalue, // pvalue, // offset in buffer to patch
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error making first new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myvalue = 56;
    
    mysrcelementid2 = dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        mysrcelementid1, // parentelementid,
        (unsigned char*)"dg_newhlist", // pname,
        11, // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error making second new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myvalue = 94;
    
    mysrcelementid3 = dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        mysrcelementid1, // parentelementid,
        (unsigned char*)"dg_movebytes", // pname,
        12, // namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error making third new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    // patch the buffer
    dg_patchaddressusinghlist(
        &BHarrayhead,
        mydesthlistid,     // id of hlist containing import symbol list
        mydestelementid1,   // parent element id of the import symbol list
        mypdestbuffer,   // address of destination buffer to patch
        *mypdestbufferlength,      // destination buffer
        mysrchlistid,      // source hlist - just using the destination hlist
        mysrcelementid1,    // should be root... but just in case it's not
        (unsigned char*)3);     // psrcbuffer)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - got an error patching the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_forthdoterrors(&BHarrayhead);
    }
    
    // +7 should be address of dg_newhlist
    if ( *((UINT64*)(mypdestbuffer + 7)) != 56+3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - first symbol not patched correctly\n");
    }
    
    // +12 should be address of dg_movebytes
    if ( *((UINT64*)(mypdestbuffer + 16)) != 94+3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - second symbol not patched correctly\n");
    }
    
    if (*(mypdestbuffer + 6) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - buffer before 1st patch corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypdestbuffer + 6)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*(mypdestbuffer + 15) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - buffer between patches corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypdestbuffer + 11)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (*(mypdestbuffer + 24) != (unsigned char)1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_patchaddressusinghlist success case - buffer after patches corrupted, got ");
        dg_writestdoutuinttodec(&BHarrayhead, (UINT64)(*(mypdestbuffer + 16)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_glu()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    unsigned char* pmyname;
    UINT64 mynamelength;
    unsigned char* pmyvalue;
    UINT64 myvaluelength;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    INT64 compareflag;
    
    UINT64 newbufferselementid;
    UINT64 newelementid;
    UINT64 symbollistelementid;
    UINT64 destsymbollistelementid;
    UINT64 destnamedbufferid;
    
    UINT64 srcsymbollistelementid;
    
    unsigned char* psrcbuffer;
    UINT64* psrcbufferlength;
    
    unsigned char* pstring;
    UINT64 stringlength;
    
    UINT64 x,y;
    Bufferhandle* pBH;
    
    UINT64 mylibraryhandle;
    
    UINT64 mysymbol1, mysymbol2, myhlibrary;
    
    UINT64 mybufferid1, mybufferid2, mybufferid3;
    
    HListidElementid myhlistidelementid;
    
    UINT64 numberofbuffers;
    
    INT64 wherefoundflag;
    UINT64 indexofkeyaftermatch;
    UINT64 sortkey;
    
    UINT64 myhere;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_glu\n");
    
    // ///////////////////////////////
    // success case - testing DestBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu DestBuf\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
      // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
      // adding new set destbuf element
    pmyvalue = (unsigned char*)"mytestbuffer";
    myvaluelength = 12;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setdestbufname,
        dg_setdestbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid1 = dg_newbuffer(
            &BHarrayhead,
            0x1000,
            0x1000,
            &pError,
            FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
      // add the buffer to the named buffer list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&mybufferid1, // pvalue,
            sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got an error adding buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got an error getting destination named buffer id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - destination buffer id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - got an error getting destination named buffer id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestBuf success case - destination buffer id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // //////////////////////////////
    // success case - testing SrcBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu SrcBuf\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set srcbuf element
    pmyvalue = (unsigned char*)"mytestbuffer";
    myvaluelength = 12;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrcbufname,
        dg_setsrcbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid1 = dg_newbuffer(
            &BHarrayhead,
            0x1000,
            0x1000,
            &pError,
            FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // add the buffer to the named buffer list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&mybufferid1, // pvalue,
            sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got an error adding buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got an error getting source named buffer id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - source buffer id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - got an error getting source named buffer id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcBuf success case - source buffer id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    // ///////////////////////////////
    // success case - testing SrcLib
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu SrcLib\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set destbuf element
    pmyvalue = (unsigned char*)"mytestlib";
    myvaluelength = 9;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrclibname,
        dg_setsrclibnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - got an error making set source list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = 0x12345678;
    
    // add a fake library to the named library list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDSHAREDLIBS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&x, // pvalue, a fake lib handle
            sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - got an error adding fake lib to named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedlib);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - got an error getting source named lib id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - source named lib id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedlib);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - got an error getting source named lib id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcLib success case - source named lib id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing SrcSymbols
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu SrcSymbols\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set srcsymbols element
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrcsymbollistname,
        dg_setsrcsymbollistnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - got an error making set source symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhlistidelementid.hlistid = 1;
    myhlistidelementid.elementid = 2;
    
    // add a fake symbol list to the named symbol list list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&myhlistidelementid, // pvalue, a fake lib handle
            sizeof(HListidElementid)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - got an error adding fake symbol list to named symbol list list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - got an error getting source named symbol list id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - source named symbol list id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - got an error getting source named symbol list id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu SrcSymbols success case - source named symbol list id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing DestSymbols
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu DestSymbols\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set destsymbols element
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setdestsymbollistname,
        dg_setdestsymbollistnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - got an error making set dest symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhlistidelementid.hlistid = 1;
    myhlistidelementid.elementid = 2;
    
    // add a fake symbol list to the named symbol list list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&myhlistidelementid, // pvalue, a fake lib handle
            sizeof(HListidElementid)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - got an error adding fake symbol list to named symbol list list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - got an error getting source named symbol list id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - destination named symbol list id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - got an error getting destination named symbol list id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu DestSymbols success case - destination named symbol list id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    // ///////////////////////////////////
    // success case - testing UINT64ValueToDS
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu UINT64ValueToDS\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new UINT64ValueToDS element
    x = 0x99774466;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = 8;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_uint64valuetodsname,
        dg_uint64valuetodsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - got an error making UINT64ValueToDS element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - got an error getting data stack depth before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - data stack not empty after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - got an error popping value off data stack after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x99774466)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu UINT64ValueToDS success case - value on data stack was not correct after gluing. Expected 0x99774466, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing ValueTo$S
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu ValueTo$S\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new ValueTo$S element
    pmyvalue = (unsigned char*)"does it work?";
    myvaluelength = 13;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_valuetostrsname,
        dg_valuetostrsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S success case - got an error making ValueTo$S element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S success case - got an error getting string stack depth before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S success case - string stack not empty after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    pstring = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &stringlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S success case - got an error getting pointer to top string after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pError = dg_comparebytes (
        pstring,
        stringlength,
        pmyvalue,
        myvaluelength,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S case - got an error trying to comparing the result string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (0 != compareflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu ValueTo$S case - string pushed to string stack did not match value string\n");
    }
    
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing HlistHere
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu HlistHere\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new HlistHere element
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_hlistherename,
        dg_hlistherenamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - got an error making HlistHere element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - got an error getting data stack depth before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - data stack not empty after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - got an error popping hlist id off data stack after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != myhlistid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - hlist id on data stack was not correct after gluing. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - got an error popping element id off data stack after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu HlistHere success case - element id on data stack was not correct after gluing. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, newelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing new named buffers
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu Bufs \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_bufferseleementname,
        dg_bufferselementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error making new buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 1
    x=1024;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer1",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error making first named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error getting number of named buffers before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - wrong number of named buffers before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error getting number of named buffers after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - wrong number of named buffers. Expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error getting id of first named buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error getting id of first named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - first named buffer's element value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pBH = dg_getpbufferhandle (
        &BHarrayhead,
        x);
    
    if (pBH->size != dg_calcnearestpagesize(1024))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - first named buffer's size wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_calcnearestpagesize(1024));
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->size);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pBH->nextunusedbyte != 1024)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - first named buffer's length wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 1024);
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->nextunusedbyte);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistlastchildofparent (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error getting id of second named buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - second named buffer's element value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    mybufferid2 = x;
    
    pBH = dg_getpbufferhandle (
        &BHarrayhead,
        x);
    
    if (pBH->size != dg_calcnearestpagesize(2048))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - second named buffer's size wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_calcnearestpagesize(2048));
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->size);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pBH->nextunusedbyte != 2048)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Bufs success case - second named buffer's length wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 2048);
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->nextunusedbyte);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing files to named buffers
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu Files \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding files element
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_fileselementname,
        dg_fileselementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error making files to named buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named file 1
    pmyvalue = (unsigned char*)"test.txt";
    myvaluelength = 8;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedfile1",
        10, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error making first file to named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named file 2
    pmyvalue = (unsigned char*)"test2.txt";
    myvaluelength = 9;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedfile2",
        10, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error making second file to named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting number of named buffers before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - wrong number of named buffers before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting number of named buffers after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - wrong number of named buffers after gluing. Expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting id of first named buffer (which holds the first file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting id of first named buffer's element value (the first loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - first named buffer's element value wrong size (the first loaded file)\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        x ,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting pointer to first named buffer (the first loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes (
        pbuffer,
        7,
        (unsigned char*)"testing",
        7,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error trying to compare the first named buffer's test string (the first loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (0 != compareflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - first named buffer's test string did not match (the first loaded file) expected >>>testing<<<, got >>>");
        dg_writestdout(
            &BHarrayhead,
            pbuffer,
            *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    x = dg_gethlistlastchildofparent (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting id of second named buffer (which holds the second file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting id of second named buffer's element value (the second loaded second file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - second named buffer's element value wrong size (the second loaded file)\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        x ,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error getting pointer to second named buffer (the second loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes (
        pbuffer,
        4,
        (unsigned char*)"yay!",
        4,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error trying to compare the second named buffer's test string (the loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (0 != compareflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - second named buffer's test string did not match (the loaded file) expected >>>yay!<<<, got >>>");
        dg_writestdout(
            &BHarrayhead,
            pbuffer,
            *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing libs to named libs
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu Libs \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding libs element
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_libsname,
        dg_libsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error making libs element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named lib 1
    pmyvalue = (unsigned char*)"dglib";
    myvaluelength = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedlib1",
        9, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error making first named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error getting number of named libs before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - wrong number of named libs before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error getting number of named libs after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - wrong number of named libs after gluing. Expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error getting id of first named lib, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error getting id of first named lib's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - first named lib's element value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pError = dg_loadlibrary(
        (const char*)DG_DIAPERGLU_LIB_NAME,
        &mylibraryhandle,
        dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error opening first lib to get handle, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != mylibraryhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - first named lib's handle wrong, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, mylibraryhandle);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_freelibrary(
        mylibraryhandle,
        dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Libs success case - got an error freeing first lib handle, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing symbols
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu Symbols \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbols element for symbollist1
    pmyvalue = (unsigned char*)"symbollist1";
    myvaluelength = 11;
    
    symbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_symbolsname,
        dg_symbolsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got an error making symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got an error getting number of named symbol lists before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - wrong number of named symbol lists before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got an error getting number of named symbol lists after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - wrong number of named symbol lists after gluing. Expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got an error getting id of first named symbol, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - got an error getting id of first named symbol lists's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(HListidElementid))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - named symbol list's value wrong size\n");
    }
    
    if (myhlistid != ((HListidElementid*)pmyvalue)->hlistid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - named symbol list's value wrong size\n");
    }
    
    if (symbollistelementid != ((HListidElementid*)pmyvalue)->elementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Symbols success case - named symbol list's value wrong size\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing call source buffer
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu (CallBuf) call source buf symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid3 = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        -1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making call buf test buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, mybufferid3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error setting current compile buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // compiling 0x99882245 N RAX MOV, RET,

    dg_compilemovntorax(&BHarrayhead, 0x99882245);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error compiling mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error compiling return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhere = dg_getbufferlength(
        &BHarrayhead,
        mybufferid3);
    
    // compiling 0x72383942 N RAX MOV, RET,
    dg_compilemovntorax(&BHarrayhead, 0x72383942);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error compiling 2nd mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error compiling 2nd return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding mybufid3 to named buffer list
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        0, // parentelementid,
        (unsigned char*)"myfuncbuf",
        9, // namelength,
        (unsigned char*)&mybufferid3, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error adding code buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbol list
    pmyvalue = (unsigned char*)"symbollist3";
    myvaluelength = 11;
    
    srcsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_symbolsname,
        dg_symbolsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding func1symbol = offset of function 1 to dest buf symbol list
    x=0; // offset of function 1
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        srcsymbollistelementid, // parentelementid,
        (unsigned char*)"myfunc1symbol",
        13, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making symbol list first child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding func2symbol = offset of function 2 to dest buf symbol list
    x=myhere; // offset of function 2
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        srcsymbollistelementid, // parentelementid,
        (unsigned char*)"myfunc2symbol",
        13, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making symbol list second child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src symbol list to symbol list 3 element
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrcsymbollistname,
        dg_setsrcsymbollistnamelength, // namelength,
        (unsigned char*)"symbollist3", // pvalue,
        11); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making third symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding element to set srcbuf to the buffer containg the compiled code in glu list
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrcbufname,
        dg_setsrcbufnamelength, // namelength,
        (unsigned char*)"myfuncbuf", // pvalue,
        9); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making set dest buf to code buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding call src buf symbol function and push result to data stack element
    pmyvalue = (unsigned char*)"myfunc1symbol";
    myvaluelength = 13;
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_calldestbuftodsname,
        dg_calldestbuftodsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call src buf function and push result to data stack element
    pmyvalue = (unsigned char*)"myfunc2symbol";
    myvaluelength = 13;
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_calldestbuftodsname,
        dg_calldestbuftodsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error popping second function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x72383942)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got wrong second function call result on data stack after function call expected 0x72383942, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got an error popping first function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x99882245)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallBuf success case - got wrong first function call result on data stack after function call expected 0x99882245, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing call destination offset
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu (CallDestOffset) call destination offset \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid3 = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        -1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error making call buf test buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, mybufferid3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error setting current compile buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // compiling 0x99882245 N EAX MOV, RET,
    // hmm this function is misnamed :-)
    dg_compilemovntorax(&BHarrayhead, 0x99882245);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error compiling mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error compiling return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhere = dg_getbufferlength(
        &BHarrayhead,
        mybufferid3);
    
    // compiling 0x72383942 N EAX MOV, RET,
    dg_compilemovntorax(&BHarrayhead, 0x72383942);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error compiling 2nd mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error compiling 2nd return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding mybufferid3 to named buffer list
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        0, // parentelementid,
        (unsigned char*)"myfuncbuf",
        9, // namelength,
        (unsigned char*)&mybufferid3, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error adding code buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding element to set destbuf to the buffer containg the compiled code in glu list
    pmyname = (unsigned char*)dg_setdestbufname;
    mynamelength = dg_setdestbufnamelength;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        (unsigned char*)"myfuncbuf", // pvalue,
        9); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error making set dest buf to code buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding call destintation offset function and push result to data stack element
    pmyname = (unsigned char*)dg_calldestoffsettodsname;
    mynamelength = dg_calldestoffsetnametodslength;
    x = 0;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call dest offset function and push result to data stack element
    pmyname = (unsigned char*)dg_calldestoffsettodsname;
    mynamelength = dg_calldestoffsetnametodslength;
    x = myhere;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error popping second function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x72383942)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got wrong second function call result on data stack after function call expected 0x72383942, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got an error popping first function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x99882245)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallDestOffset success case - got wrong first function call result on data stack after function call expected 0x99882245, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing call source lib
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu (CallLib) call source lib symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding libs element
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_libsname,
        dg_libsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error making libs element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named lib 1
    pmyvalue = (unsigned char*)DG_DIAPERGLU_LIB_NAME;
    myvaluelength = DG_DIAPERGLU_LIB_NAME_LENGTH;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedlib1",
        9, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error making first named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src lib to to named lib 1
    pmyvalue = (unsigned char*)"namedlib1";
    myvaluelength = 9;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrclibname,
        dg_setsrclibnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error making set src named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call source lib function "dg_forthoneplus"
    pmyvalue = (unsigned char*)"dg_forthoneplus";
    myvaluelength = 15;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_calllibname,
        dg_calllibnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error making first call lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call source lib function "dg_forthoneplus"
    pmyvalue = (unsigned char*)"dg_forthoneplus";
    myvaluelength = 15;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_calllibname,
        dg_calllibnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error making second call lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 99);
    
   
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got an error popping function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != 101)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu CallLib success case - got wrong result on data stack after function call expected 101, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing LinkLib
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu (LinkLib) link source buf symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_bufferseleementname,
        dg_bufferselementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding libs element
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_libsname,
        dg_libsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making libs element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named lib 1
    pmyvalue = (unsigned char*)"dglib";
    myvaluelength = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedlib1",
        9, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making first named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src lib to to named lib 1
    pmyvalue = (unsigned char*)"namedlib1";
    myvaluelength = 9;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrclibname,
        dg_setsrclibnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making set src named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setdestbufname,
        dg_setdestbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link from current src lib element
    // namedbuffer2 is the current destbuf
    // namedlib1 is the current src lib which represents libdiaperglu.dglu
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_linklibname,
        dg_linklibnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making link lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to dg_forthdup element
    x=11; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"dg_forthdup",
        11, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding link to dg_forthoneplus element
    x=3; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"dg_forthoneplus",
        15, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error making second lib link child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
   
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		DG_DIAPERGLU_LIB_NAME_LENGTH, // length,
		(unsigned char*)DG_DIAPERGLU_LIB_NAME); // psrc)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error pushing the library name to the string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_forthopenlibrarystring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error opening the library, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlibrary = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error popping the library handle from the data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthdrop(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error dropping wordlist id from the data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		11, // length,
		(unsigned char*)"dg_forthdup"); // psrc)
    
    dg_pushdatastack(&BHarrayhead, myhlibrary);
    
    dg_forthfindlibrarysymbol(&BHarrayhead);
    
    mysymbol1 = dg_popdatastack(&BHarrayhead);
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		15, // length,
		(unsigned char*)"dg_forthoneplus"); // psrc)
    
    dg_pushdatastack(&BHarrayhead, myhlibrary);
    
    dg_forthfindlibrarysymbol(&BHarrayhead);
    
    mysymbol2 = dg_popdatastack(&BHarrayhead);
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid2 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid2,
        &pbufferlength);
    
    x = *((UINT64*)(pbuffer + 3));
    
    if (mysymbol2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got wrong address for patch lib symbol 2, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, mysymbol2);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = *((UINT64*)(pbuffer + 11));
    
    if (mysymbol1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkLib success case - got wrong address for patch lib symbol 1, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, mysymbol1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    

    // ///////////////////////////////////
    // success case - testing LinkNewBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu (LinkNewBuf) link new buffer \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_bufferseleementname,
        dg_bufferselementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setdestbufname,
        dg_setdestbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link base address of a new buffer
    // namedbuffer2 is the current destbuf
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_linknewbufname,
        dg_linknewbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making link lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset from base address of new buffer with length 0x1000
    y=0x1000;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=21; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset from base address of new buffer with length 0x2000
    y=0x2000;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=28; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid1,
        &pbufferlength);
    
    // doing it this way assumes no buffers have been freed
    //  and that the buffer ids of the last two allocated buffers
    //  hmm... I think all the stuff going on doesn't free any buffers...
    numberofbuffers = BHarrayhead.nextunusedbyte / sizeof (Bufferhandle);
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        numberofbuffers - 2,
        &psrcbufferlength);
    
    x = *((UINT64*)(pbuffer + 21));
    
    if (((UINT64)psrcbuffer) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got wrong address for patch new buf 2, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        numberofbuffers-1,
        &psrcbufferlength);
    
    x = *((UINT64*)(pbuffer + 28));
    
    if (((UINT64)psrcbuffer) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkNewBuf success case - got wrong address for patch new buf 1, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing LinkBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu (LinkBuf) link source buf symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_bufferseleementname,
        dg_bufferselementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 1
    x=1024;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer1",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making first named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbols element for symbollist1
    pmyvalue = (unsigned char*)"symbollist1";
    myvaluelength = 11;
    
    symbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_symbolsname,
        dg_symbolsnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding <symbol1>7
    x=7;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        symbollistelementid, // parentelementid,
        (unsigned char*)"symbol1",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making first symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding <symbol2>11
    x=15;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        symbollistelementid, // parentelementid,
        (unsigned char*)"symbol2",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making second symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding <symbol3>15
    x=15;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        symbollistelementid, // parentelementid,
        (unsigned char*)"symbol3",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making third symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src buf to named buffer 1
    pmyvalue = (unsigned char*)"namedbuffer1";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrcbufname,
        dg_setsrcbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setdestbufname,
        dg_setdestbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set source symbol list to symbollist1
    pmyvalue = (unsigned char*)"symbollist1";
    myvaluelength = 11;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrcsymbollistname,
        dg_setsrcsymbollistnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making set src symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link from current source symbol list and source buffer
    // namedbuffer2 is the current destbuf
    // namedbuffer1 is the current srcbuf
    // symbolist1 is the current symbollist
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_linkbufname,
        dg_linkbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making link lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to symbol1
    x=21; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"symbol1",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to symbol2
    x=32; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"symbol2",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error making second lib link child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error getting id of first named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - first named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid2,
        &psrcbufferlength);
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid2 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid2,
        &pbufferlength);
    
    x = *((UINT64*)(pbuffer + 21));
    
    if (((UINT64)psrcbuffer + 7) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got wrong address for patch buf symbol 1, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = *((UINT64*)(pbuffer + 32));
    
    if (((UINT64)psrcbuffer + 15) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkBuf success case - got wrong address for patch buf symbol 2, expected 11, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing LinkOffset
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu (LinkOffset) link new buffer \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_bufferseleementname,
        dg_bufferselementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 1
    x=1024;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer1",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making first named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setdestbufname,
        dg_setdestbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src buf to named buffer 1 element
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_setsrcbufname,
        dg_setsrcbufnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making set src named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link offset in dest buffer
    // namedbuffer2 is the current destbuf
    //  so... from destbuf to destbuf
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_linkoffsetname,
        dg_linkoffsetnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making link offset element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset
    y=3; // src offset in dest buffer
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=21; // dest link offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making first link offset child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset from base address of new buffer with length 0x2000
    y=11; // src offset in dest buffer
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=32; // dest link offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error making first link offset child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid1,
        &pbufferlength);
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got an error getting id of first named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - first named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid1,
        &psrcbufferlength);
    
    x = *((UINT64*)(pbuffer + 21));
    
    if (((UINT64)psrcbuffer + 3) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got wrong address for patch offset 1, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = *((UINT64*)(pbuffer + 32));
    
    if (((UINT64)psrcbuffer + 11) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu LinkOffset success case - got wrong address for offset 2, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing Load Hlists
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu load named hierarchical lists \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    
    // making packed hlist file to load
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error making new hlist that will be pack into a file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"rooty";
    myvaluelength = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)pmyvalue,
        myvaluelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error making first new hlist root element for packed hlist file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid1 = dg_packhlist (
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error packing first new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, mybufferid1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error pushing packed hlist bufferid to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		13, // length,
		(unsigned char*)"testfile.pkhl"); // psrc)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error pushing packed hlist filename to string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsavefilestring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error saving pack hlist testfile, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding load packed hlist files to named hlists element
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_hlistfileselementname,
        dg_hlistfileselementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding load named hlist file element
    pmyvalue = (unsigned char*)&"testfile.pkhl";
    myvaluelength = 13;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedhlist2",
        11, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    wherefoundflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"namedhlist2",
        11,
        DG_NAMEDHLISTS_HLISTID,
        DG_ROOT_ELEMENTID,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &sortkey);
            
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL Load Hlists success case - got an error finding first named lib in named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (wherefoundflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL Load Hlists success case - loaded hlist's name not found in named hlist list.\n");
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDHLISTS_HLISTID,
        sortkey,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error getting id of loaded named hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - loaded named hlist element's value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pmyname = dg_getshlistelementnom (
        &BHarrayhead,
        x,
        DG_ROOT_ELEMENTID,
        &mynamelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Load Hlists success case - got an error getting loaded hlist's root element's name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes (
        pmyname,
        mynamelength,
        (unsigned char*)"rooty",
        5,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - got an error trying to compare the loaded hlist's root element's name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu Files success case - loaded hlist's root element name is incorrect, expected rooty, got ");
        dg_writestdout(&BHarrayhead, pmyname, mynamelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing NGlu
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_glu NGlu named hlist \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    
    // making hlist to NGlu
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got error making Nglu hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyname = (unsigned char*)dg_glulistelementname;
    mynamelength = dg_glulistelementnamelength;
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got an error making NGlu hlist's root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding nglu list new named buffers element
    x = DG_GLUFUNCBUFS;
    pmyname = (unsigned char*)&x;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got an error making NGlu list's new buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new named buffer element
    x = 0x1000;
    pmyname = (unsigned char*)"myfirstnamedbuffer";
    mynamelength = 18;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got an error making NGlu list's new buffer element got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // add nglu hlist to the named list list
    pmyname = (unsigned char*)"mynglunamedhlist";
    mynamelength = 16;
    pmyvalue = (unsigned char*)&myhlistid;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDHLISTS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got an error adding NGlu list to named hlist list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding NGlu named hlist element
    pmyvalue = (unsigned char*)"mynglunamedhlist";
    myvaluelength = 16;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)dg_ngluname,
        dg_nglunamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_glu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_glu NGlu success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    wherefoundflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myfirstnamedbuffer",
        18,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &sortkey);
            
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL NGlu success case - got an error finding first named buffer in named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (wherefoundflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL NGlu success case - named buffer's name not found in named buffer list.\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
}

void testdg_nglu()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    unsigned char* pmyname;
    UINT64 mynamelength;
    unsigned char* pmyvalue;
    UINT64 myvaluelength;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    INT64 compareflag;
    
    UINT64 newbufferselementid;
    UINT64 newelementid;
    UINT64 symbollistelementid;
    UINT64 destsymbollistelementid;
    UINT64 destnamedbufferid;
    
    UINT64 srcsymbollistelementid;
    
    unsigned char* psrcbuffer;
    UINT64* psrcbufferlength;
    
    unsigned char* pstring;
    UINT64 stringlength;
    
    UINT64 x,y;
    Bufferhandle* pBH;
    
    UINT64 mylibraryhandle;
    
    UINT64 mysymbol1, mysymbol2, myhlibrary;
    
    UINT64 mybufferid1, mybufferid2, mybufferid3;
    
    HListidElementid myhlistidelementid;
    
    UINT64 numberofbuffers;
    
    INT64 wherefoundflag;
    UINT64 indexofkeyaftermatch;
    UINT64 sortkey;
    
    UINT64 myhere;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_nglu\n");
    
    // ///////////////////////////////
    // success case - testing DestBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu DestBuf\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
      // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
      // adding new set destbuf element
    y = DG_GLUFUNCDESTBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"mytestbuffer";
    myvaluelength = 12;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid1 = dg_newbuffer(
            &BHarrayhead,
            0x1000,
            0x1000,
            &pError,
            FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
      // add the buffer to the named buffer list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&mybufferid1, // pvalue,
            sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got an error adding buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got an error getting destination named buffer id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - destination buffer id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - got an error getting destination named buffer id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestBuf success case - destination buffer id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // //////////////////////////////
    // success case - testing SrcBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu SrcBuf\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set srcbuf element
    y = DG_GLUFUNCSRCBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"mytestbuffer";
    myvaluelength = 12;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid1 = dg_newbuffer(
            &BHarrayhead,
            0x1000,
            0x1000,
            &pError,
            FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got an error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // add the buffer to the named buffer list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&mybufferid1, // pvalue,
            sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got an error adding buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got an error getting source named buffer id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - source buffer id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    destnamedbufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - got an error getting source named buffer id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (destnamedbufferid  != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcBuf success case - source buffer id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    // ///////////////////////////////
    // success case - testing SrcLib
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu SrcLib\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set srclib element
    y = DG_GLUFUNCSRCLIB;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"mytestlib";
    myvaluelength = 9;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - got an error making set source list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = 0x12345678;
    
    // add a fake library to the named library list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDSHAREDLIBS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&x, // pvalue, a fake lib handle
            sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - got an error adding fake lib to named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedlib);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - got an error getting source named lib id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - source named lib id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedlib);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - got an error getting source named lib id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcLib success case - source named lib id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing SrcSymbols
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu SrcSymbols\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set srcsymbols element
    y = DG_GLUFUNCSRCSYMBOLS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - got an error making set source symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhlistidelementid.hlistid = 1;
    myhlistidelementid.elementid = 2;
    
    // add a fake symbol list to the named symbol list list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&myhlistidelementid, // pvalue, a fake lib handle
            sizeof(HListidElementid)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - got an error adding fake symbol list to named symbol list list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - got an error getting source named symbol list id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - source named symbol list id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - got an error getting source named symbol list id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu SrcSymbols success case - source named symbol list id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing DestSymbols
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu DestSymbols\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new set destsymbols element
    y=DG_GLUFUNCDESTSYMBOLS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - got an error making set dest symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhlistidelementid.hlistid = 1;
    myhlistidelementid.elementid = 2;
    
    // add a fake symbol list to the named symbol list list
        newelementid = dg_newhlistelement (
            &BHarrayhead,
            DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pmyvalue,      // pointer to name of named buffer
            myvaluelength, // length of named buffer's name,
            (unsigned char*)&myhlistidelementid, // pvalue, a fake lib handle
            sizeof(HListidElementid)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - got an error adding fake symbol list to named symbol list list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - got an error getting source named symbol list id before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - destination named symbol list id not DG_ENDOFLIST after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedsymbollist);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - got an error getting destination named symbol list id after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu DestSymbols success case - destination named symbol list id not correct after gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    // ///////////////////////////////////
    // success case - testing UINT64ValueToDS
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu UINT64ValueToDS\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new UINT64ValueToDS element
    y = DG_GLUFUNCUINT64VALUETODS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x = 0x99774466;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = 8;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - got an error making UINT64ValueToDS element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - got an error getting data stack depth before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - data stack not empty after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - got an error popping value off data stack after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x99774466)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu UINT64ValueToDS success case - value on data stack was not correct after gluing. Expected 0x99774466, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing ValueTo$S
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu ValueTo$S\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new ValueTo$S element
    y = DG_GLUFUNCVALUETOSTRS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"does it work?";
    myvaluelength = 13;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S success case - got an error making ValueTo$S element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S success case - got an error getting string stack depth before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S success case - string stack not empty after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    pstring = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        &stringlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S success case - got an error getting pointer to top string after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pError = dg_comparebytes (
        pstring,
        stringlength,
        pmyvalue,
        myvaluelength,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S case - got an error trying to comparing the result string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (0 != compareflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu ValueTo$S case - string pushed to string stack did not match value string\n");
    }
    
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing HlistHere
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu HlistHere\n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new HlistHere element
    y = DG_GLUFUNCHLISTHERE;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - got an error making HlistHere element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - got an error getting data stack depth before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - data stack not empty after initialization and before gluing.\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - got an error popping hlist id off data stack after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != myhlistid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - hlist id on data stack was not correct after gluing. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popbufferuint64(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - got an error popping element id off data stack after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != newelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu HlistHere success case - element id on data stack was not correct after gluing. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, newelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing new named buffers
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu Bufs \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    y = DG_GLUFUNCBUFS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error making new buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 1
    x=1024;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer1",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error making first named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error getting number of named buffers before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - wrong number of named buffers before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error getting number of named buffers after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - wrong number of named buffers. Expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error getting id of first named buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error getting id of first named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - first named buffer's element value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pBH = dg_getpbufferhandle (
        &BHarrayhead,
        x);
    
    if (pBH->size != dg_calcnearestpagesize(1024))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - first named buffer's size wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_calcnearestpagesize(1024));
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->size);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pBH->nextunusedbyte != 1024)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - first named buffer's length wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 1024);
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->nextunusedbyte);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistlastchildofparent (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error getting id of second named buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - second named buffer's element value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    mybufferid2 = x;
    
    pBH = dg_getpbufferhandle (
        &BHarrayhead,
        x);
    
    if (pBH->size != dg_calcnearestpagesize(2048))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - second named buffer's size wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, dg_calcnearestpagesize(2048));
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->size);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pBH->nextunusedbyte != 2048)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Bufs success case - second named buffer's length wrong. Expected ");
        dg_writestdoutuinttodec(&BHarrayhead, 2048);
        dg_printzerostring(&BHarrayhead, (unsigned char*)". Got ");
        dg_writestdoutuinttodec(&BHarrayhead, pBH->nextunusedbyte);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing files to named buffers
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu Files \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding files element
    y = DG_GLUFUNCFILES;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error making files to named buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named file 1
    pmyvalue = (unsigned char*)"test.txt";
    myvaluelength = 8;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedfile1",
        10, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error making first file to named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named file 2
    pmyvalue = (unsigned char*)"test2.txt";
    myvaluelength = 9;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedfile2",
        10, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error making second file to named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting number of named buffers before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - wrong number of named buffers before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting number of named buffers after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - wrong number of named buffers after gluing. Expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting id of first named buffer (which holds the first file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting id of first named buffer's element value (the first loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - first named buffer's element value wrong size (the first loaded file)\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        x ,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting pointer to first named buffer (the first loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes (
        pbuffer,
        7,
        (unsigned char*)"testing",
        7,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error trying to compare the first named buffer's test string (the first loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (0 != compareflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - first named buffer's test string did not match (the first loaded file) expected >>>testing<<<, got >>>");
        dg_writestdout(
            &BHarrayhead,
            pbuffer,
            *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    x = dg_gethlistlastchildofparent (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting id of second named buffer (which holds the second file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting id of second named buffer's element value (the second loaded second file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - second named buffer's element value wrong size (the second loaded file)\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer (
        &BHarrayhead,
        x ,
        &pbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error getting pointer to second named buffer (the second loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes (
        pbuffer,
        4,
        (unsigned char*)"yay!",
        4,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error trying to compare the second named buffer's test string (the loaded file), got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (0 != compareflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - second named buffer's test string did not match (the loaded file) expected >>>yay!<<<, got >>>");
        dg_writestdout(
            &BHarrayhead,
            pbuffer,
            *pbufferlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing libs to named libs
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu Libs \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding libs element
    y = DG_GLUFUNCLIBS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error making libs element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named lib 1
    pmyvalue = (unsigned char*)"dglib";
    myvaluelength = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedlib1",
        9, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error making first named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error getting number of named libs before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - wrong number of named libs before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error getting number of named libs after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - wrong number of named libs after gluing. Expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error getting id of first named lib, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error getting id of first named lib's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - first named lib's element value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pError = dg_loadlibrary(
        (const char*)DG_DIAPERGLU_LIB_NAME,
        &mylibraryhandle,
        dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error opening first lib to get handle, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != mylibraryhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - first named lib's handle wrong, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, mylibraryhandle);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_freelibrary(
        mylibraryhandle,
        dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Libs success case - got an error freeing first lib handle, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing symbols
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu Symbols \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbols element for symbollist1
    y = DG_GLUFUNCSYMBOLS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"symbollist1";
    myvaluelength = 11;
    
    symbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got an error making symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got an error getting number of named symbol lists before gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - wrong number of named symbol lists before gluing. Expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getnumberofsortedchildren(
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got an error getting number of named symbol lists after gluing, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - wrong number of named symbol lists after gluing. Expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_gethlistfirstchild (
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        DG_ROOT_ELEMENTID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got an error getting id of first named symbol, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - got an error getting id of first named symbol lists's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(HListidElementid))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - named symbol list's value wrong size\n");
    }
    
    if (myhlistid != ((HListidElementid*)pmyvalue)->hlistid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - named symbol list's value wrong size\n");
    }
    
    if (symbollistelementid != ((HListidElementid*)pmyvalue)->elementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Symbols success case - named symbol list's value wrong size\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing call source buffer
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu (CallBuf) call source buf symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid3 = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        -1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making call buf test buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, mybufferid3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error setting current compile buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // compiling 0x99882245 N EAX MOV, RET,
    // hmm this function is misnamed :-)
    dg_compilemovntorax(&BHarrayhead, 0x99882245);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error compiling mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error compiling return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhere = dg_getbufferlength(
        &BHarrayhead,
        mybufferid3);
    
    // compiling 0x72383942 N EAX MOV, RET,
    dg_compilemovntorax(&BHarrayhead, 0x72383942);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error compiling 2nd mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error compiling 2nd return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding mybufid3 to named buffer list
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        0, // parentelementid,
        (unsigned char*)"myfuncbuf",
        9, // namelength,
        (unsigned char*)&mybufferid3, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error adding code buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbol list
    y = DG_GLUFUNCSYMBOLS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"symbollist3";
    myvaluelength = 11;
    
    srcsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding func1symbol = offset of function 1 to dest buf symbol list
    x=0; // offset of function 1
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        srcsymbollistelementid, // parentelementid,
        (unsigned char*)"myfunc1symbol",
        13, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making symbol list first child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding func2symbol = offset of function 2 to dest buf symbol list
    x=myhere; // offset of function 2
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        srcsymbollistelementid, // parentelementid,
        (unsigned char*)"myfunc2symbol",
        13, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making symbol list second child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src symbol list to symbol list 3 element
    y = DG_GLUFUNCSRCSYMBOLS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        (unsigned char*)"symbollist3", // pvalue,
        11); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making third symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding element to set srcbuf to the buffer containg the compiled code in glu list
    y = DG_GLUFUNCSRCBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        (unsigned char*)"myfuncbuf", // pvalue,
        9); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making set dest buf to code buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding call src buf symbol function and push result to data stack element
    y = DG_GLUFUNCCALLBUFTODS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"myfunc1symbol";
    myvaluelength = 13;
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call src buf function and push result to data stack element
    y = DG_GLUFUNCCALLBUFTODS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"myfunc2symbol";
    myvaluelength = 13;
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error popping second function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x72383942)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got wrong second function call result on data stack after function call expected 0x72383942, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got an error popping first function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x99882245)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallBuf success case - got wrong first function call result on data stack after function call expected 0x99882245, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing call destination offset
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu (CallDestOffset) call destination offset \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid3 = dg_newbuffer(
        &BHarrayhead,
        0x1000,
        -1,
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error making call buf test buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer, mybufferid3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error setting current compile buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // compiling 0x99882245 N EAX MOV, RET,
    // hmm this function is misnamed :-)
    dg_compilemovntorax(&BHarrayhead, 0x99882245);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error compiling mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error compiling return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhere = dg_getbufferlength(
        &BHarrayhead,
        mybufferid3);
    
    // compiling 0x72383942 N EAX MOV, RET,
    dg_compilemovntorax(&BHarrayhead, 0x72383942);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error compiling 2nd mov n to eax, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_compilereturn(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error compiling 2nd return, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding mybufferid3 to named buffer list
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        0, // parentelementid,
        (unsigned char*)"myfuncbuf",
        9, // namelength,
        (unsigned char*)&mybufferid3, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error adding code buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding element to set destbuf to the buffer containg the compiled code in glu list
    y = DG_GLUFUNCDESTBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        (unsigned char*)"myfuncbuf", // pvalue,
        9); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error making set dest buf to code buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding call destintation offset function and push result to data stack element
    y = DG_GLUFUNCCALLDESTOFFSETTODS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x = 0;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call destination offset function and push result to data stack element
    y = DG_GLUFUNCCALLDESTOFFSETTODS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x = myhere;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    destsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error making first call buf element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error popping second function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x72383942)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got wrong second function call result on data stack after function call expected 0x72383942, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got an error popping first function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x99882245)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallDestOffset success case - got wrong first function call result on data stack after function call expected 0x99882245, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing call source lib
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu (CallLib) call source lib symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding libs element
    y = DG_GLUFUNCLIBS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error making libs element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named lib 1
    pmyvalue = (unsigned char*)"dglib";
    myvaluelength = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedlib1",
        9, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error making first named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src lib to to named lib 1
    y = DG_GLUFUNCSRCLIB;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedlib1";
    myvaluelength = 9;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error making set src named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call source lib function "dg_forthoneplus"
    y = DG_GLUFUNCCALLLIB;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"dg_forthoneplus";
    myvaluelength = 15;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error making first call lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding call source lib function "dg_forthoneplus"
    y = DG_GLUFUNCCALLLIB;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"dg_forthoneplus";
    myvaluelength = 15;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error making second call lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 99);
    
   
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got an error popping function call result from data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != 101)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu CallLib success case - got wrong result on data stack after function call expected 101, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdots(&BHarrayhead);
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing LinkLib
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu (LinkLib) link source buf symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    y = DG_GLUFUNCBUFS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding libs element
    y = DG_GLUFUNCLIBS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making libs element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named lib 1
    pmyvalue = (unsigned char*)"dglib";
    myvaluelength = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"namedlib1",
        9, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making first named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src lib to to named lib 1
    y = DG_GLUFUNCSRCLIB;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedlib1";
    myvaluelength = 9;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making set src named lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    y = DG_GLUFUNCDESTBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedlib1";
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link from current src lib element
    // namedbuffer2 is the current destbuf
    // namedlib1 is the current src lib which represents libdiaperglu.dglu
    y = DG_GLUFUNCLINKLIB;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making link lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to dg_forthdup element
    x=11; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"dg_forthdup",
        11, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding link to dg_forthoneplus element
    x=3; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"dg_forthoneplus",
        15, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error making second lib link child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
   
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		DG_DIAPERGLU_LIB_NAME_LENGTH, // length,
		(unsigned char*)DG_DIAPERGLU_LIB_NAME); // psrc)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error pushing the library name to the string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_forthopenlibrarystring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error opening the library, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlibrary = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error popping the library handle from the data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthdrop(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error dropping wordlist id from the data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		11, // length,
		(unsigned char*)"dg_forthdup"); // psrc)
    
    dg_pushdatastack(&BHarrayhead, myhlibrary);
    
    dg_forthfindlibrarysymbol(&BHarrayhead);
    
    mysymbol1 = dg_popdatastack(&BHarrayhead);
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		15, // length,
		(unsigned char*)"dg_forthoneplus"); // psrc)
    
    dg_pushdatastack(&BHarrayhead, myhlibrary);
    
    dg_forthfindlibrarysymbol(&BHarrayhead);
    
    mysymbol2 = dg_popdatastack(&BHarrayhead);
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid2 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid2,
        &pbufferlength);
    
    x = *((UINT64*)(pbuffer + 3));
    
    if (mysymbol2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got wrong address for patch lib symbol 2, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, mysymbol2);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = *((UINT64*)(pbuffer + 11));
    
    if (mysymbol1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkLib success case - got wrong address for patch lib symbol 1, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, mysymbol1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    

    // ///////////////////////////////////
    // success case - testing LinkNewBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu (LinkNewBuf) link new buffer \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    y = DG_GLUFUNCBUFS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    y = DG_GLUFUNCDESTBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link base address of a new buffer
    // namedbuffer2 is the current destbuf
    y = DG_GLUFUNCLINKNEWBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedbuffer2";
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making link lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset from base address of new buffer with length 0x1000
    y=0x1000;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=21; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset from base address of new buffer with length 0x2000
    y=0x2000;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=28; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid1,
        &pbufferlength);
    
    // doing it this way assumes no buffers have been freed
    //  and that the buffer ids of the last two allocated buffers
    //  hmm... I think all the stuff going on doesn't free any buffers...
    numberofbuffers = BHarrayhead.nextunusedbyte / sizeof (Bufferhandle);
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        numberofbuffers - 2,
        &psrcbufferlength);
    
    x = *((UINT64*)(pbuffer + 21));
    
    if (((UINT64)psrcbuffer) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got wrong address for patch new buf 2, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        numberofbuffers-1,
        &psrcbufferlength);
    
    x = *((UINT64*)(pbuffer + 28));
    
    if (((UINT64)psrcbuffer) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkNewBuf success case - got wrong address for patch new buf 1, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing LinkBuf
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu (LinkBuf) link source buf symbol \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    y = DG_GLUFUNCBUFS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 1
    x=1024;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer1",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making first named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbols element for symbollist1
    y = DG_GLUFUNCSYMBOLS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"symbollist1";
    myvaluelength = 11;
    
    symbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making symbol list parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding <symbol1>7
    x=7;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        symbollistelementid, // parentelementid,
        (unsigned char*)"symbol1",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making first symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding <symbol2>11
    x=11;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        symbollistelementid, // parentelementid,
        (unsigned char*)"symbol2",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making second symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding <symbol3>15
    x=15;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        symbollistelementid, // parentelementid,
        (unsigned char*)"symbol3",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making third symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src buf to named buffer 1
    y = DG_GLUFUNCSRCBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedbuffer1";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    y = DG_GLUFUNCDESTBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set source symbol list to symbollist1
    y = DG_GLUFUNCSRCSYMBOLS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"symbollist1";
    myvaluelength = 11;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making set src symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link from current source symbol list and source buffer
    // namedbuffer2 is the current destbuf
    // namedbuffer1 is the current srcbuf
    // symbolist1 is the current symbollist
    y = DG_GLUFUNCLINKBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making link lib element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to symbol1
    x=21; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"symbol1",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making first link lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to symbol2
    x=32; // offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        (unsigned char*)"symbol2",
        7, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error making second lib link child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error getting id of first named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - first named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid2,
        &psrcbufferlength);
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid2 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid2,
        &pbufferlength);
    
    x = *((UINT64*)(pbuffer + 21));
    
    if (((UINT64)psrcbuffer + 7) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got wrong address for patch buf symbol 1, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = *((UINT64*)(pbuffer + 32));
    
    if (((UINT64)psrcbuffer + 11) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkBuf success case - got wrong address for patch buf symbol 2, expected 11, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing LinkOffset
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu (LinkOffset) link new buffer \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new buffers element
    y = DG_GLUFUNCBUFS;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 2
    x=2048;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer2",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding named buffer 1
    x=1024;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedbuffer1",
        12, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making first named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set dest buf to named buffer 2 element
    y = DG_GLUFUNCDESTBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedbuffer2";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making set dest named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding set src buf to named buffer 1 element
    y = DG_GLUFUNCSRCBUF;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"namedbuffer1";
    myvaluelength = 12;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making set src named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link offset in dest buffer
    // namedbuffer2 is the current destbuf
    // namedbuffer1 is the current srcbuf
    y = DG_GLUFUNCLINKOFFSET;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);

    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making link offset element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset
    y=3; // src offset in dest buffer
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=21; // dest link offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making first link offset child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding link to offset from base address of new buffer with length 0x2000
    y=11; // src offset in dest buffer
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    x=32; // dest link offset in dest buffer
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newelementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error making first link offset child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error getting id of second named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - second named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid1,
        &pbufferlength);
    
    x = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf);
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        x,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got an error getting id of first named buffer's element value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - first named buffer's element value wrong size\n");
    }
    
    mybufferid1 = *((UINT64*)pmyvalue);
    
    psrcbuffer = dg_getpbuffer(
        &BHarrayhead,
        mybufferid1,
        &psrcbufferlength);
    
    x = *((UINT64*)(pbuffer + 21));
    
    if (((UINT64)psrcbuffer + 3) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got wrong address for patch offset 1, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = *((UINT64*)(pbuffer + 32));
    
    if (((UINT64)psrcbuffer + 11) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu LinkOffset success case - got wrong address for offset 2, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)psrcbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing Load Hlists
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu load named hierarchical lists \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    
    // making packed hlist file to load
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error making new hlist that will be pack into a file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"rooty";
    myvaluelength = 5;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)pmyvalue,
        myvaluelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error making first new hlist root element for packed hlist file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mybufferid1 = dg_packhlist (
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error packing first new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, mybufferid1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error pushing packed hlist bufferid to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // UINT64 offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // UINT64 stringbufferid,
		13, // length,
		(unsigned char*)"testfile.pkhl"); // psrc)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error pushing packed hlist filename to string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsavefilestring(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error saving pack hlist testfile, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding load packed hlist files to named hlists element
    y = DG_GLUFUNCHFILES;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding load named hlist file element
    pmyvalue = (unsigned char*)&"testfile.pkhl";
    myvaluelength = 13;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        (unsigned char*)"namedhlist2",
        11, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error making second named buffer element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    wherefoundflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"namedhlist2",
        11,
        DG_NAMEDHLISTS_HLISTID,
        DG_ROOT_ELEMENTID,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &sortkey);
            
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error finding first named lib in named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (wherefoundflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - loaded hlist's name not found in named hlist list.\n");
    }
    
    pmyvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDHLISTS_HLISTID,
        sortkey,
        &myvaluelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error getting id of loaded named hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myvaluelength != sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gnlu Load Hlists success case - loaded named hlist element's value wrong size\n");
    }
    
    x = *((UINT64*)pmyvalue);
    
    pmyname = dg_getshlistelementnom (
        &BHarrayhead,
        x,
        DG_ROOT_ELEMENTID,
        &mynamelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Load Hlists success case - got an error getting loaded hlist's root element's name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes (
        pmyname,
        mynamelength,
        (unsigned char*)"rooty",
        5,
        &compareflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - got an error trying to compare the loaded hlist's root element's name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu Files success case - loaded hlist's root element name is incorrect, expected rooty, got ");
        dg_writestdout(&BHarrayhead, pmyname, mynamelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
    
    // ///////////////////////////////////
    // success case - testing NGlu
    dg_printzerostring(&BHarrayhead, (unsigned char*)"  testing dg_nglu NGlu named hlist \n");
    
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    
    // making hlist to NGlu
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got error making Nglu hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyname = (unsigned char*)dg_nglulistelementname;
    mynamelength = dg_nglulistelementnamelength;
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got an error making NGlu hlist's root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding nglu list new named buffers element
    x = DG_GLUFUNCBUFS;
    pmyname = (unsigned char*)&x;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got an error making NGlu list's new buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding new named buffer element
    x = 0x1000;
    pmyname = (unsigned char*)"myfirstnamedbuffer";
    mynamelength = 18;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        newbufferselementid, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got an error making NGlu list's new buffer element got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // add nglu hlist to the named list list
    pmyname = (unsigned char*)"mynglunamedhlist";
    mynamelength = 16;
    pmyvalue = (unsigned char*)&myhlistid;
    myvaluelength = sizeof(UINT64);
    
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDHLISTS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got an error adding NGlu list to named hlist list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding nglu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding NGlu named hlist element
    y = DG_GLUFUNCNGLU;
    pmyname = (unsigned char*)&y;
    mynamelength = sizeof(UINT64);
    pmyvalue = (unsigned char*)"mynglunamedhlist";
    myvaluelength = 16;
    
    newbufferselementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got an error making buffers element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_nglu(
        &BHarrayhead,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - got errors doing glu list, got:\n");
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_freeallbuffers(&BHarrayhead);
        dg_clearerrors(&BHarrayhead);
        return;
    }
    
    wherefoundflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myfirstnamedbuffer",
        18,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &sortkey);
            
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAILdg_nglu NGlu success case - got an error finding first named buffer in named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (wherefoundflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_nglu NGlu success case - named buffer's name not found in named buffer list.\n");
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
    
}

void testdg_loadsharedliblist()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    UINT64 libsparentelementid;
    
    Hlistheader myhlistheader;
    


    unsigned char* pvalue;
    UINT64 valuelength;
    
    INT64 wherefoundflag;
    UINT64 indexofkeyaftermatch;
    UINT64 sortkey;
    
    UINT64 x;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_loadsharedliblist\n");
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist  success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        (UINT64)-1, // parentelementid,
        (unsigned char*)"rooty",
        5, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error making third symbol list first child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    libsparentelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        (unsigned char*)dg_libsname,
        dg_libsnamelength, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error making load libs parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        libsparentelementid, // parentelementid,
        (unsigned char*)"myfirstlib",
        10, // namelength,
        (unsigned char*)"dglib", // pvalue,
        5); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error making first lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        libsparentelementid, // parentelementid,
        (unsigned char*)"mysecondlib",
        11, // namelength,
        (unsigned char*)"dglib", // pvalue,
        5); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error making first lib child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_loadsharedliblist(
        &BHarrayhead,
        myhlistid,
        libsparentelementid,
        (unsigned char*)"",     // pparentvalue
        0,                      // parentvaluelength,
        &myhlistheader);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error loading lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
    
    wherefoundflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myfirstlib",
        10,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &sortkey);
            
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error finding first named lib in named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (0 != wherefoundflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - first lib not found in named lib list\n");
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        sortkey,
        &valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error getting first lib handle from named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
        DG_DIAPERGLU_LIB_NAME_LENGTH,
        (unsigned char*)DG_DIAPERGLU_LIB_NAME);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error pushing library string name to string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthopenlibrarystring (&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error opening libdiaperglu library, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error popping lib handle of data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != *((UINT64*)pvalue))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - first lib handle wrong\n");
        return;
    }
    
    wherefoundflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"mysecondlib",
        11,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_ROOT_ELEMENTID,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &sortkey);
            
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error finding second named lib in named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (0 != wherefoundflag)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - second lib not found in named lib list\n");
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        &BHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        sortkey,
        &valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - got an error getting second lib handle from named lib list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != *((UINT64*)pvalue))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_loadsharedliblist success case - second lib handle wrong\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_getnamedsymbollisthideid ()
{
    Bufferhandle BHarrayhead;
    
    unsigned char* pmyname;
    UINT64 mynamelength;
    unsigned char* pmyvalue;
    UINT64 myvaluelength;
    
    UINT64 namedsymbollisthlistid;
    UINT64 namedsymbollistelementid;
    
    UINT64 myresulthlistid;
    UINT64 myresultelementid;
    
    UINT64 mysymbolelementid;
    
    const char* pError;
    
    struct HListidElementid myhlistidelementid;
    
    UINT64 x;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getnamedsymbollisthideid \n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    namedsymbollisthlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // making glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        namedsymbollisthlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbol list element
    pmyname = (unsigned char*)dg_setsrcsymbollistname;
    mynamelength = dg_setsrcsymbollistnamelength;
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    namedsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        namedsymbollisthlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got an error making set source symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbol
    x = 0x1133224499778866;
    pmyname = (unsigned char*)"mysymbolname1";
    mynamelength = 13;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    mysymbolelementid = dg_newhlistelement (
        &BHarrayhead,
        namedsymbollisthlistid, // hlistid,
        namedsymbollistelementid, // parentelementid,
        (unsigned char*)
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got an error making a symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    myhlistidelementid.hlistid = namedsymbollisthlistid;
    myhlistidelementid.elementid = namedsymbollistelementid;
    
    // adding symbol list to the named symbol list list
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pmyvalue,      // pname = pointer to name of symbol list
        myvaluelength, // name length = length of name of symbol list
        (unsigned char*)&myhlistidelementid, // pvalue
        sizeof(HListidElementid));           // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got an error adding fake symbol list to named symbol list list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    myresultelementid = dg_getnamedsymbollisthideid (
        &BHarrayhead,
        pmyvalue,
        myvaluelength,
        &myresulthlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got an error calling dg_getnamedsymbollisthideid, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (myresulthlistid != namedsymbollisthlistid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got wrong hlist id, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, namedsymbollisthlistid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got  ");
        dg_writestdoutuinttodec(&BHarrayhead, myresulthlistid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (myresultelementid != namedsymbollistelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getnamedsymbollisthideid success case - got wrong element id, expected ");
        dg_writestdoutuinttodec(&BHarrayhead, myresultelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got  ");
        dg_writestdoutuinttodec(&BHarrayhead, mysymbolelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
}


void testdg_hsymbolnametovalue ()
{
    Bufferhandle BHarrayhead;
    
    unsigned char* pmyname;
    UINT64 mynamelength;
    unsigned char* pmyvalue;
    UINT64 myvaluelength;
    
    UINT64 namedsymbollisthlistid;
    UINT64 namedsymbollistelementid;
    
    UINT64 myresulthlistid;
    UINT64 myresultelementid;
    
    UINT64 mysymbolelementid;
    
    const char* pError;
    
    struct HListidElementid myhlistidelementid;
    
    UINT64 x;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_hsymbolnametovalue \n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    namedsymbollisthlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hsymbolnametovalue success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // making glu list root
    pmyvalue = (unsigned char*)"";
    myvaluelength = 0;
    
    dg_newhlistelement (
        &BHarrayhead,
        namedsymbollisthlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hsymbolnametovalue success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbol list element
    pmyname = (unsigned char*)dg_setsrcsymbollistname;
    mynamelength = dg_setsrcsymbollistnamelength;
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    namedsymbollistelementid = dg_newhlistelement (
        &BHarrayhead,
        namedsymbollisthlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hsymbolnametovalue success case - got an error making set source symbol list element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding symbol
    x = 0x1133224499778866;
    pmyname = (unsigned char*)"mysymbolname1";
    mynamelength = 13;
    pmyvalue = (unsigned char*)&x;
    myvaluelength = sizeof(UINT64);
    
    mysymbolelementid = dg_newhlistelement (
        &BHarrayhead,
        namedsymbollisthlistid, // hlistid,
        namedsymbollistelementid, // parentelementid,
        (unsigned char*)
        pmyname,
        mynamelength, // namelength,
        pmyvalue, // pvalue,
        myvaluelength); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hsymbolnametovalue success case - got an error making a symbol element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pmyvalue = (unsigned char*)"mytestsymbollist";
    myvaluelength = 16;
    
    myhlistidelementid.hlistid = namedsymbollisthlistid;
    myhlistidelementid.elementid = namedsymbollistelementid;
    
    // adding symbol list to the named symbol list list
    dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pmyvalue,      // pname = pointer to name of symbol list
        myvaluelength, // name length = length of name of symbol list
        (unsigned char*)&myhlistidelementid, // pvalue
        sizeof(HListidElementid));           // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hsymbolnametovalue success case - got an error adding fake symbol list to named symbol list list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_hsymbolnametovalue (
        &BHarrayhead,
        pmyname,
        mynamelength,
        namedsymbollisthlistid,
        namedsymbollistelementid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hsymbolnametovalue success case - got an error calling dg_getnamedsymbollisthideid, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_forthdoterrors(&BHarrayhead);
        return;
    }
    
    if (x != 0x1133224499778866)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hsymbolnametovalue success case - got wrong hlist id, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x1133224499778866);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got  ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_clearerrors(&BHarrayhead);  dg_freeallbuffers(&BHarrayhead);

    
}

void testdg_namedbufnametoeid ()
{
    Bufferhandle BHarrayhead;
    
    UINT64 mybufferid;
    unsigned char* mypbuffer;
    UINT64* mypbufferlength;
    
    UINT64 destnamedbufferid;
    
    const char* pError;
    
    unsigned char* pbuffername;
    UINT64 buffernamelength;
    
    UINT64 x;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_namedbufnametoeid \n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    // need to create a buffer and fill it with a number
    mybufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoeid success case - got an error making the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to use the buffer
    dg_growbuffer (
        &BHarrayhead,
		mybufferid,
		1000,  // in bytes
		&pError,
		FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoeid success case - got an error growing the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need pointer to the buffer
    mypbuffer = dg_getpbuffer (
        &BHarrayhead,
        mybufferid,
        &mypbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoeid success case - got an error getting a pointer to the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_fillwithbyte (
        mypbuffer,
        *mypbufferlength,
        1); // value
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoeid success case - got an error filling the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffername = (unsigned char*)&"mydestbuffer";
    buffernamelength = 12;
    
    // add the buffer to the named buffer list
    destnamedbufferid = dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pbuffername, // pname,
        buffernamelength, // namelength,
        (unsigned char*)&mybufferid, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoeid success case - got an error adding dest buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_namedbufnametoeid (
        &BHarrayhead,
        pbuffername,
        buffernamelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoeid success case - got an error calling dg_namedbufnametoeid, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != destnamedbufferid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoeid success case - got wrong element id, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, destnamedbufferid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got  ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}


void testdg_namedbufnametobufid ()
{
    Bufferhandle BHarrayhead;
    
    UINT64 mybufferid;
    unsigned char* mypbuffer;
    UINT64* mypbufferlength;
    
    UINT64 destnamedbufferid;
    
    const char* pError;
    
    unsigned char* pbuffername;
    UINT64 buffernamelength;
    
    UINT64 x;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_namedbufnametobufid \n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    // need to create a buffer and fill it with a number
    mybufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametobufid success case - got an error making the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to use the buffer
    dg_growbuffer (
        &BHarrayhead,
		mybufferid,
		1000,  // in bytes
		&pError,
		FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametobufid success case - got an error growing the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need pointer to the buffer
    mypbuffer = dg_getpbuffer (
        &BHarrayhead,
        mybufferid,
        &mypbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametobufid success case - got an error getting a pointer to the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_fillwithbyte (
        mypbuffer,
        *mypbufferlength,
        1); // value
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametobufid success case - got an error filling the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffername = (unsigned char*)&"mydestbuffer";
    buffernamelength = 12;
    
    // add the buffer to the named buffer list
    destnamedbufferid = dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pbuffername, // pname,
        buffernamelength, // namelength,
        (unsigned char*)&mybufferid, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametobufid success case - got an error adding dest buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_namedbufnametobufid (
        &BHarrayhead,
        pbuffername,
        buffernamelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametobufid success case - got an error calling dg_namedbufnametoeid, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != mybufferid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametobufid success case - got wrong element id, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, mybufferid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got  ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}


void testdg_namedbufnametoaddr ()
{
    Bufferhandle BHarrayhead;
    
    UINT64 mybufferid;
    unsigned char* mypbuffer;
    UINT64* mypbufferlength;
    
    UINT64 destnamedbufferid;
    
    const char* pError;
    
    unsigned char* pbuffername;
    UINT64 buffernamelength;
    
    UINT64 x;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_namedbufnametoaddr \n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // this is needed because, at this time, the open library function creates a wordlist 5/15/2016
    dg_inithlists (&BHarrayhead);
    
    // need to create a buffer and fill it with a number
    mybufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoaddr success case - got an error making the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to use the buffer
    dg_growbuffer (
        &BHarrayhead,
		mybufferid,
		1000,  // in bytes
		&pError,
		FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoaddr success case - got an error growing the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need pointer to the buffer
    mypbuffer = dg_getpbuffer (
        &BHarrayhead,
        mybufferid,
        &mypbufferlength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoaddr success case - got an error getting a pointer to the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_fillwithbyte (
        mypbuffer,
        *mypbufferlength,
        1); // value
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoaddr success case - got an error filling the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pbuffername = (unsigned char*)&"mydestbuffer";
    buffernamelength = 12;
    
    // add the buffer to the named buffer list
    destnamedbufferid = dg_newhlistelement (
        &BHarrayhead,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pbuffername, // pname,
        buffernamelength, // namelength,
        (unsigned char*)&mybufferid, // pvalue,
        sizeof(UINT64)); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoaddr success case - got an error adding dest buffer to named buffer list, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = (UINT64)dg_namedbufnametoaddr (
        &BHarrayhead,
        pbuffername,
        buffernamelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoaddr success case - got an error calling dg_namedbufnametoeid, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != (UINT64)mypbuffer)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namedbufnametoaddr success case - got wrong element id, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)mypbuffer);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got  ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}
