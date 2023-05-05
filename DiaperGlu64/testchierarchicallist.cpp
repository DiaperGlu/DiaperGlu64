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



void testdg_gethlistheaderarrayheader()
{
    Bufferhandle BHarrayhead;
    
    Freeablelstringarrayheader myflstah;
    const char* pError;
    
    UINT64 hlistheaderarraybufferid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_gethlistheaderarrayheader\n");
    
    //  error getting hlistheaderarraybufferid
    dg_initbuffers(&BHarrayhead);
    
    dg_gethlistheaderarrayheader(
        &BHarrayhead,
        &myflstah,
        sizeof(Freeablelstringarrayheader));
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheaderarrayheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader error getting hlistheaderarraybufferid case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader error getting hlistheaderarraybufferid case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    
    
    //  hlistheaderarray flstring bufferid not initialized case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_gethlistheaderarrayheader(
        &BHarrayhead,
        &myflstah,
        sizeof(Freeablelstringarrayheader));
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheaderarrayheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader hlistheaderarray flstring bufferid not initialized case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_forthhlistheaderarraybufferidname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader hlistheaderarray flstring bufferid not initialized case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_bufferidnotinbharray)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader hlistheaderarray flstring bufferid not initialized case - got wrong error 2 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    
    // error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    hlistheaderarraybufferid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_hlistheaderbuffer, hlistheaderarraybufferid);
    
    dg_gethlistheaderarrayheader(
        &BHarrayhead,
        &myflstah,
        sizeof(Freeablelstringarrayheader));
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheaderarrayheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader error getting hlist header array header case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getbuffersegmentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader error getting hlist header array header case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    
    
    // bad magic case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    hlistheaderarraybufferid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_hlistheaderbuffer, hlistheaderarraybufferid);
        
    myflstah.magic = 0;
    
    dg_pushbuffersegment (
        &BHarrayhead,
        hlistheaderarraybufferid,
        sizeof(Freeablelstringarrayheader),
        (unsigned char*)&myflstah);
        
    dg_gethlistheaderarrayheader(
        &BHarrayhead,
        &myflstah,
        sizeof(Freeablelstringarrayheader));
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheaderarrayheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader bad magic case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader bad magic case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    hlistheaderarraybufferid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);
    
    dg_putbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, dg_hlistheaderbuffer, hlistheaderarraybufferid);
        
    myflstah.magic = dg_freeablelstringheadermagic;
    
    dg_pushbuffersegment (
        &BHarrayhead,
        hlistheaderarraybufferid,
        sizeof(Freeablelstringarrayheader),
        (unsigned char*)&myflstah);
        
    dg_gethlistheaderarrayheader(
        &BHarrayhead,
        &myflstah,
        sizeof(Freeablelstringarrayheader));
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheaderarrayheader success case - got error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_querycreatehlistheaderarray()
{
    Bufferhandle BHarrayhead;
    
    Freeablelstringarrayheader myflstah;
    Freeablelstringarrayheader myflstah2;
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_querycreatehlistheaderarray\n");
    
    //  error getting hlistbufferid case
    dg_initbuffers(&BHarrayhead);
    
    dg_querycreatehlistheaderarray(&BHarrayhead);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_querycreatehlistheaderarrayname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray error getting hlistheaderarraybufferid case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getbufferuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray error getting hlistheaderarraybufferid case - got wrong error 1 below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    // no hlist header array yet success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_querycreatehlistheaderarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray no hlist header array yet success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    dg_gethlistheaderarrayheader(
        &BHarrayhead,
        &myflstah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray no hlist header array yet success case - got an error getting hlist header array header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }

    if (myflstah.magic != dg_freeablelstringheadermagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray no hlist header array yet success case - bad magic for hlist header array header\n");
    }
    
    // hlist header array already exists success case
    dg_querycreatehlistheaderarray(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray hlist header array already exists success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    dg_gethlistheaderarrayheader(
        &BHarrayhead,
        &myflstah2,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray hlist header array already exists success case - got an error getting hlist header array header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    if (myflstah.magic != myflstah2.magic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray hlist header array already exists success case - hlist header array header magic changed\n");
    }
    
    if (myflstah.lstringoffsetbufferid != myflstah2.lstringoffsetbufferid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray hlist header array already exists success case - hlist header array header lstringoffsetbufferid changed\n");
    }
    
    if (myflstah.lstringstringbufferid != myflstah2.lstringstringbufferid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray hlist header array already exists success case - hlist header array header lstringstringbufferid changed\n");
    }
    
    if (myflstah.firstfreeid != myflstah2.firstfreeid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_querycreatehlistheaderarray hlist header array already exists success case - hlist header array header firstfreeid changed\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_gethlistheader()
{
    Bufferhandle BHarrayhead;
    
    Hlistheader myhlistheader;
   
    const char* pError;
    
    UINT64 hlistheaderarraybufferid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_gethlistheader\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_gethlistheader(
        &BHarrayhead,
        0,
        &myhlistheader,
        sizeof(Hlistheader));
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheader error getting hlist header array header case - got wrong error on top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheaderarrayheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheader error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheaderarrayheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error copying hlist header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_querycreatehlistheaderarray(&BHarrayhead);
    
    dg_gethlistheader(
        &BHarrayhead,
        0,
        &myhlistheader,
        sizeof(Hlistheader));
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheader error copying hlist header case - got wrong error on top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromlstringnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheader error copying hlist header case - got wrong error 1 below top expected dg_copysfromlstringnname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_querycreatehlistheaderarray(&BHarrayhead);
    
    hlistheaderarraybufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_hlistheaderbuffer);
    
    dg_newfreeablelstring (
        &BHarrayhead,
        hlistheaderarraybufferid);
        
    myhlistheader.magic = dg_hlistheadermagic;
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        hlistheaderarraybufferid,
        0,
        0,
        (unsigned char*)&myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheader success case - got error making hlist header\n");
    }
    
    myhlistheader.magic = 0;
       
    dg_gethlistheader(
        &BHarrayhead,
        0,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistheader success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_newhlist()
{
    Bufferhandle BHarrayhead;
    
    UINT64 myhlistid;
    const char* pError;
    
    UINT64 n;
    
    Hlistheader myhlistheader;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newhlist\n");
#ifndef DGLU_NO_DIAPER   
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_newhlistname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist error getting hlist header array header case - got wrong error on top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_querycreatehlistheaderarrayname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheaderarrayheader, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist error getting hlist header array header case - got wrong return value, expected DG_ENDOFLIST\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error allocating freeable lstring for hlist elements case - hard to test - need ability to force out of memory condition
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    
    dg_freeallbuffers(&BHarrayhead);

    dg_clearerrors(&BHarrayhead);
#endif    
    // first hlist success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myhlistheader.magic = 0;
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - got an error getting hlist header for test, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // magic checked in dg_gethlistheader
    if ((UINT64)dg_badbufferid == myhlistheader.elementheaderflstrbufid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - elementheaderflstrbufid not allocated\n");
    }
    
    //if (dg_badbufferid == myhlistheader.taglstroffsetbufid)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - taglstroffsetbufid not allocated\n");
    //}
    
    //if (dg_badbufferid == myhlistheader.taglstrstringbufid)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - taglstrstringbufid not allocated\n");
    //}
    
    if ((UINT64)dg_badbufferid == myhlistheader.namelstroffsetbufid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - namelstroffsetbufid not allocated\n");
    }
    
    if ((UINT64)dg_badbufferid == myhlistheader.namelstrstringbufid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - namelstrstringbufid not allocated\n");
    }
    
    if ((UINT64)dg_badbufferid == myhlistheader.valuelstroffsetbufid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - valuelstroffsetbufid not allocated\n");
    }
    
    if ((UINT64)dg_badbufferid == myhlistheader.valuelstrstringbufid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - valuelstrstringbufid not allocated\n");
    }
    
    if ((UINT64)dg_badbufferid == myhlistheader.sortedchildidslstroffsetbufid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - sortedchildidslstroffsetbufid not allocated\n");
    }
    
    if ((UINT64)dg_badbufferid == myhlistheader.sortedchildidslstrstringbufid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - sortedchildidslstrstringbufid not allocated\n");
    }
       
    if (myhlistheader.namelstroffsetbufid != (myhlistheader.elementheaderflstrbufid + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - namelstroffsetbufid wrong buffer id\n");
    }
    
    if (myhlistheader.namelstrstringbufid != (myhlistheader.namelstroffsetbufid + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - namelstrstringbufid wrong buffer id\n");
    }
    
    if (myhlistheader.valuelstroffsetbufid != (myhlistheader.namelstrstringbufid + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - valuelstroffsetbufid wrong buffer id\n");
    }
    
    if (myhlistheader.valuelstrstringbufid != (myhlistheader.valuelstroffsetbufid + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - valuelstrstringbufid wrong buffer id\n");
    }
    
    if (myhlistheader.sortedchildidslstroffsetbufid != (myhlistheader.valuelstrstringbufid + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - sortedchildidslstroffsetbufid wrong buffer id\n");
    }
    
    if (myhlistheader.sortedchildidslstrstringbufid != (myhlistheader.sortedchildidslstroffsetbufid + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - sortedchildidslstroffsetbufid wrong buffer id\n");
    }
    
    n = dg_newbuffer(
        &BHarrayhead,  
        1000,
        10000,
        &pError,
        FORTH_FALSE);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - error making new buffer for test\n");
    }
    
    if (n != (myhlistheader.sortedchildidslstrstringbufid + 1))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlist first hlist success case - number of buffers allocated is wrong\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}



void testdg_freehlist()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    Hlistheader myhlistheader;
    UINT64 hlistheaderarraybufferid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_freehlist\n");
#ifndef DGLU_NO_DIAPER    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_freehlist (
        &BHarrayhead,
        1); // hlistheaderid)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_freehlistname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist error getting hlist header array header case - got wrong error on top expected dg_freehlistname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    //  freeing hlist 0 error case
    dg_initbuffers(&BHarrayhead);
    
    dg_freehlist (
        &BHarrayhead,
        0); // hlistheaderid)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_freehlistname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing hlist 0 error case - got wrong error on top expected dg_freehlistname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_tryingtofreehlist0error)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing hlist 0 error case - got wrong error 1 below top expected dg_tryingtofreehlist0error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
 #endif   
    // first success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - got an error getting hlist header for test, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freehlist (
        &BHarrayhead,
        myhlistid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - got an error freeing hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
//    pError = dg_checkbuffer (
//        &BHarrayhead,
//        myhlistheader.taglstroffsetbufid);
        
//    if (dg_success == pError)
//    {
//        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - taglstroffsetbufid is not free\n");
//    }
    
//    pError = dg_checkbuffer (
//        &BHarrayhead,
//        myhlistheader.taglstrstringbufid);
        
//    if (dg_success == pError)
//    {
//        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - taglstrstringbufid is not free\n");
//    }

    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - namelstroffsetbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.namelstrstringbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - namelstrstringbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - valuelstroffsetbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.valuelstrstringbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - valuelstrstringbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - sortedchildidslstroffsetbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.sortedchildidslstrstringbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - sortedchildidslstrstringbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - elementheaderflstrbufid is not free\n");
    }
    
      // checking if hlist array header is free
    hlistheaderarraybufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_hlistheaderbuffer);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - error getting hlist array header array buffer id\n");
        return;
    }
    
    dg_isfreeablelstringfree (
        &BHarrayhead,
        hlistheaderarraybufferid,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist first success case - hlist header array header freeable lstring is not free\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // freeing middle of 3 success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_newhlist(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - got an error getting hlist header for test, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freehlist (
        &BHarrayhead,
        myhlistid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - got an error freeing hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
   
//    pError = dg_checkbuffer (
//        &BHarrayhead,
//        myhlistheader.taglstroffsetbufid);
        
//    if (dg_success == pError)
//    {
//        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - taglstroffsetbufid is not free\n");
//    }
    
//    pError = dg_checkbuffer (
//        &BHarrayhead,
//        myhlistheader.taglstrstringbufid);
        
//    if (dg_success == pError)
//    {
//        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - taglstrstringbufid is not free\n");
//    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - namelstroffsetbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.namelstrstringbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - namelstrstringbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - valuelstroffsetbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.valuelstrstringbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - valuelstrstringbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - sortedchildidslstroffsetbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.sortedchildidslstrstringbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - sortedchildidslstrstringbufid is not free\n");
    }
    
    pError = dg_checkbuffer (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_success == pError)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - elementheaderflstrbufid is not free\n");
    }
    
      // checking if hlist array header is free
    hlistheaderarraybufferid = dg_getbufferuint64(
        &BHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_hlistheaderbuffer);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - error getting hlist array header array buffer id\n");
        return;
    }
    
    dg_isfreeablelstringfree (
        &BHarrayhead,
        hlistheaderarraybufferid,
        myhlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlist freeing middle of 3 success case - hlist header array header freeable lstring is not free\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_linklasthlistchildelement()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    Hlistheader myhlistheader;
    
    Hlistelementheader myhlistlementheader;
    
    Freeablelstringarrayheader myelementheaderflstrah;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_linklasthlistchildelement\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting hlist header array header case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  error getting hlist element freeable lstring array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting hlist element freeable lstring array header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting hlist element freeable lstring array header case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
   dg_freefreeablelstringarray(&BHarrayhead,  myhlistheader.elementheaderflstrbufid);
   
   if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting hlist element freeable lstring array header case - got an error freeing hlist element freeable lstring array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting hlist header array header case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting hlist header array header case - got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  error getting pointer to element header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to element header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to element header case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to element header case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    //  element bad magic case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element bad magic case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlistlementheader.magic = 0;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element bad magic case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element bad magic case - got wrong error 1 below top expected dg_badmagicerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  element header too small case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element header too small case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader) - 1);    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element header too small case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element header too small case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_structuretoosmallerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement element header too small case - got wrong error 2 below top expected dg_structuretoosmallerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    //  error getting pointer to parent element header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to parent element header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to parent element header case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to parent element header case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_pushlstring (
        &BHarrayhead,
        myelementheaderflstrah.lstringoffsetbufferid, // offsetbufferid,
        myelementheaderflstrah.lstringstringbufferid, // stringbufferid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // psrc);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to parent element header case - got an error pushing element header onto lstring stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // assumes element ids are allocated sequentially from 0
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementheaderid,
        1); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to parent element header case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to parent element header case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  parent element header too small case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlistlementheader.magic = dg_hlistelementmagic;
    
        // parent id 0
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader) - 1);    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // child id 1
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // assumes element ids are allocated sequentially from 0
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_structuretoosmallerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got wrong error 2 below top expected dg_structuretoosmallerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    //  parent element bad magic case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = 0;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element bad magic case - got wrong error 1 below top expected dg_badmagicerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  parent element header to small case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader) - 1);    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_structuretoosmallerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent element header too small case - got wrong error 2 below top expected dg_structuretoosmallerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // parent has no children success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.lastchildelementid = DG_ENDOFLIST;
    myhlistlementheader.firstchildelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)
        
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error linking last child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error getting hlist element freeable lstring header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // get parent element header
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		0, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error parent element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - parent's last child element id incorrect expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.firstchildelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - parent's first child element id incorrect expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.firstchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - parent's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // get child element
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		1, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - got an error new child element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - child's parent element id incorrect expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement parent has no children success case - child's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error getting pointer to last child case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.lastchildelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // new child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)
        
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error getting pointer to last child case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }   
    
    
    // error last child's header too small case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.lastchildelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // new child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // previous last child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader) - 1);    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)
        
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_structuretoosmallerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child's header too small case - got wrong error 2 below top expected dg_structuretoosmallerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    // error last child bad magic case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.lastchildelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // new child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // previous last child id 1
    myhlistlementheader.magic = 0;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)
        
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_linklasthlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement error last child bad magic case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success 1 previous last child case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.lastchildelementid = 2;
    myhlistlementheader.firstchildelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // new child id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // previous last child id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.parentelementid = 0;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)
        
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error linking new last child, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error getting hlist element freeable lstring header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // get parent element header
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		0, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error parent element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - parent's last child element id incorrect expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.firstchildelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - parent's first child element id incorrect expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.firstchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - parent's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // get child element
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		1, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error new child element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's parent element id incorrect expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.previoussiblingelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's previous element id incorrect expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's next element id incorrect expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // get old previous child element
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		2, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - got an error new child element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's parent element id incorrect expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.nextsiblingelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's next element id incorrect expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's previous element id incorrect expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement success 1 previous last child case - child's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // 2nd new last child success case
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.parentelementid = 0;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        3, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        
    dg_linklasthlistchildelement (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        3, // UINT64 elementheaderid,
        0); // UINT64 parentelementheaderid)
        
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - got an error linking new last child, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // get parent element header again
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		0, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - got an error parent element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - parent's last child element id incorrect expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.firstchildelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - parent's first child element id incorrect expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.firstchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - parent's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // get new child element
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		3, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - got an error new child element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's parent element id incorrect expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.previoussiblingelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's previous element id incorrect expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's next element id incorrect expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // get old previous child element
    dg_copysfromlstringn (
        &BHarrayhead,
		myelementheaderflstrah.lstringoffsetbufferid, //			UINT64 offsetbufferid,
		myelementheaderflstrah.lstringstringbufferid, //			UINT64 stringbufferid,
		1, //			UINT64 stringid,
        0, //            UINT64 offset,
        sizeof(Hlistelementheader), //            UINT64 length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - got an error new child element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's parent element id incorrect expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.nextsiblingelementid != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's next element id incorrect expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.previoussiblingelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's previous element id incorrect expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
 
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_linklasthlistchildelement 2nd new last child success case - child's magic incorrect expected element magic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_unlinkhlistchildelement()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    Hlistheader myhlistheader;
    
    Hlistelementheader myhlistlementheader;
    
    Freeablelstringarrayheader myelementheaderflstrah;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_unlinkhlistchildelement\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist header array header case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  error getting hlist element freeable lstring array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
   dg_freefreeablelstringarray(&BHarrayhead,  myhlistheader.elementheaderflstrbufid);
   
   if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got an error freeing hlist element freeable lstring array, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got wrong error on top expected dg_linklasthlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copyflstrheadertosname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got wrong error 1 below top expected dg_copyflstrheadertosname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    ////////////////////////////////////////////////
    //  error getting pointer to element header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got wrong error on top expected dg_unlinkhlistchildelement, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting hlist element freeable lstring array header case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    //  element bad magic case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element bad magic case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlistlementheader.magic = 0;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element bad magic case - got wrong error on top expected dg_unlinkhlistchildelement, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element bad magic case - got wrong error 1 below top expected dg_badmagicerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  element header too small case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element header too small case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myhlistlementheader.magic = dg_hlistelementmagic;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader) - 1);    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element header too small case - got wrong error on top expected dg_unlinkhlistchildelement, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element header too small case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_structuretoosmallerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element header too small case - got wrong error 2 below top expected dg_structuretoosmallerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    //////////////////////////////////////////////////
    //  error getting pointer to previous sibling case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to previous sibling case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to previous sibling case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to previous sibling case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // making element header
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 1;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // making parent element header
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to previous sibling case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to previous sibling case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  previous sibling element header too small case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader) - 1);    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // previous sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 1;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // assumes element ids are allocated sequentially from 0
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_structuretoosmallerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement previous sibling element header too small case - got wrong error 2 below top expected dg_structuretoosmallerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    //  previous sibling element bad magic case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // previous sibling element id 2
    myhlistlementheader.magic = 0;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 1;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad magic case - got wrong error 1 below top expected dg_badmagicerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  previous sibling element bad parent case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // previous sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 1;
    myhlistlementheader.nextsiblingelementid = 1;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_hlistpreviousparentbad)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad parent case - got wrong error 1 below top expected dg_hlistpreviousparentbad, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  previous sibling element bad next case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // previous sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 0;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_hlistpreviousnextbad)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement parent element bad next case - got wrong error 1 below top expected dg_hlistpreviousnextbad, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    //////////////////////////////////////////////////
    //  error getting pointer to next sibling case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // making element header
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 1;
    myhlistlementheader.nextsiblingelementid = 2;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // making parent element header
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement error getting pointer to next sibling case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  next sibling element header too small case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 2;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // next sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader) - 1);    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // assumes element ids are allocated sequentially from 0
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_structuretoosmallerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element header too small case - got wrong error 2 below top expected dg_structuretoosmallerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    //  next sibling element bad parent case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 2;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // next sibling element id 2
    myhlistlementheader.magic = 0;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmagicerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got wrong error 1 below top expected dg_badmagicerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  next sibling element bad parent case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 2;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // next sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 1;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_hlistnextparentbad)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad parent case - got wrong error 1 below top expected dg_hlistnextparentbad, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  next sibling element bad previous case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 2;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // next sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 0;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_hlistnextpreviousbad)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement next sibling element bad previous case - got wrong error 1 below top expected dg_hlistnextpreviousbad, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // removing child no previous sibling success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.firstchildelementid = 1;
    myhlistlementheader.lastchildelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 2;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // next sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        2); // elementheaderid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - got an error unlinking child, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - parent id changed expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - next id changed expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - previous id changed expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.firstchildelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - parent's first child wrong. Expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.firstchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no previous sibling success case - parent's last child wrong. Expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // removing child no next sibling success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.lastchildelementid = 1;
    myhlistlementheader.firstchildelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // next sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 1;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - got an error unlinking child, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // getting remaining child
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - parent id changed expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - next id changed expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - previous id changed expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // getting parent
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.lastchildelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - last child id incorrect, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.firstchildelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child no next sibling success case - first child id incorrect, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.firstchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // removing child with both siblings success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.lastchildelementid = 3;
    myhlistlementheader.firstchildelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 3;
    myhlistlementheader.previoussiblingelementid = 2;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // previous sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 1;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // next sibling element id 3
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        3, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - got an error unlinking child, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // getting previous sibling
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - parent id changed expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - next id changed expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - previous id changed expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // getting next sibling
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        3, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - parent id changed expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - next id changed expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - previous id changed expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // getting parent
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.lastchildelementid != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - last child id incorrect, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.firstchildelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing child with both siblings success case - first child id incorrect, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // removing root - no parent -case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.lastchildelementid = 1;
    myhlistlementheader.firstchildelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -casee - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error unlinking child, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // getting parent
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstrid
        0, // offset,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&myhlistlementheader); // pdest)
        
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - last child id incorrect, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.firstchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - first child id incorrect, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.firstchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // removing only child case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.lastchildelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)
    
      // basically a crash test
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement removing root - no parent -case - got an error unlinking child, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    //  element is parent's last child and has next sibling error case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_copyflstrheadertos(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
        // parent id 0
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = DG_ENDOFLIST;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.lastchildelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error inserting into freeable lstring 0, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // element id 1
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = 2;
    myhlistlementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // next sibling element id 2
    myhlistlementheader.magic = dg_hlistelementmagic;
    myhlistlementheader.parentelementid = 0;
    myhlistlementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistlementheader.previoussiblingelementid = 1;
    
    dg_newfreeablelstring (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error new freeable lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    dg_insertsintoflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        2, // flstringid
        0, // offset,
        (unsigned char*)&myhlistlementheader,
        sizeof(Hlistelementheader));    
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got an error inserting into freeable lstring 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    dg_unlinkhlistchildelement (
        &BHarrayhead,
        0, // hlistheaderid,
        1); // elementheaderid)

        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_unlinkhlistchildelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got wrong error on top expected dg_unlinkhlistchildelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_hlistparentlastchildbad)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_unlinkhlistchildelement element is parent's last child and has next sibling error case - got wrong error 1 below top expected dg_hlistparentlastchildbad, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}



void testdg_newhlistelement()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    UINT64 element1;
    UINT64 element2;
    UINT64 element3;
    UINT64 element4;
    UINT64 element5;
    UINT64 element6;
    UINT64 element7;
    UINT64 element8;
    UINT64 element9;
    
    Hlistheader myhlistheader;
    
    Hlistelementheader myhlistlementheader;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newhlistelement\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_newhlistelement (
        &BHarrayhead,
        0, // hlistid,
        0, // parentelementid,
        //0, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_newhlistelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement error getting hlist header array header case - got wrong error on top expected dg_newhlistelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    // adding root element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong name length, expected 6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        6,
        (unsigned char*)"myname",
        6,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error comparing name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - name lstring wrong, expected 'myname', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong value length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        7,
        (unsigned char*)"myvalue",
        7,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error comparing value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - value lstring wrong, expected 'myvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // checking element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong parent, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong next sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong previous sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    //if (myhlistlementheader.key != 1)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element success case - got wrong key, expected 0, got ");
    //    dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.key);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}
    
    
      // adding first child success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //2, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong name length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        7,
        (unsigned char*)"myname1",
        7,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error comparing name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - name lstring wrong, expected 'myname', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong value length, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        8,
        (unsigned char*)"myvalue1",
        8,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error comparing value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - value lstring wrong, expected 'myvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // checking element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong parent, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong next sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong previous sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    //if (myhlistlementheader.key != 2)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child success case - got wrong key, expected 2, got ");
    //    dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.key);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

      // need to check parent's sort list

    
    // adding second child success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //5, // key,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        //(unsigned char*)"mytag2", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong name length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        7,
        (unsigned char*)"myname2",
        7,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error comparing name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - name lstring wrong, expected 'myname', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong value length, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        8,
        (unsigned char*)"myvalue2",
        8,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error comparing value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - value lstring wrong, expected 'myvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong parent, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong next sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong previous sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    //if (myhlistlementheader.key != 5)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong key, expected 2, got ");
    //    dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.key);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

    // need to check parent's sort list
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error getting pointer to parent's child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong parent's child sort keys length, expected 16, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong parent's first sort key, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[1] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong parent's first sort key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // checking previous sibling's next sibling link
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        1,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child success case - got wrong next sibling, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    // adding third child success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //3, // key,
        (unsigned char*)"myname3", // pname,
        7, // namelength,
        //(unsigned char*)"mytag3", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong name length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        7,
        (unsigned char*)"myname3",
        7,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error comparing name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - name lstring wrong, expected 'myname', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong value length, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        8,
        (unsigned char*)"myvalue3",
        8,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error comparing value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - value lstring wrong, expected 'myvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong parent, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong next sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong previous sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    //if (myhlistlementheader.key != 3)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong key, expected 2, got ");
    //    dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.key);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

    // need to check parent's sort list
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got an error getting pointer to parent's child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong parent's child sort keys length, expected 24, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong parent's first sort key, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[1] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong parent's first sort key, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[2] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child success case - got wrong parent's first sort key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[2]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    // adding grand child to second child success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        2, // parentelementid,
        //7, // key,
        (unsigned char*)"myname4", // pname,
        7, // namelength,
        //(unsigned char*)"mytag4", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue4", // pvalue,
        8); // valuelength);
        
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong name length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        7,
        (unsigned char*)"myname4",
        7,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error comparing name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - name lstring wrong, expected 'myname', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong value length, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        8,
        (unsigned char*)"myvalue4",
        8,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error comparing value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - value lstring wrong, expected 'myvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong parent, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong next sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong previous sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    //if (myhlistlementheader.key != 7)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong key, expected 2, got ");
    //    dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.key);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}

    // need to check parent's sort list
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        2,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got an error getting pointer to parent's child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong parent's child sort keys length, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding grand child to second child success case - got wrong parent's first sort key, expected 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // adding root element default name sorted success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
     
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL adding root element default name sorted success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL adding root element default name sorted success case - got wrong name length, expected 6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        6,
        (unsigned char*)"myname",
        6,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL adding root element default name sorted success case - got an error comparing name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - name lstring wrong, expected 'myname', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong value length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        7,
        (unsigned char*)"myvalue",
        7,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got an error comparing value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - value lstring wrong, expected 'myvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // checking element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong parent, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong next sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong previous sibling, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    //if (myhlistlementheader.key != 1)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding root element default name sorted success case - got wrong key, expected 0, got ");
    //    dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.key);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}
    
    // adding first child default name sorted success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"dog", // pname,
        3, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child default name sorted success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child default name sorted success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child default name sorted success case - got wrong child sort keys length, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding first child default name sorted success case - got wrong child sort key[0], expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding second child default name sorted success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"cat", // pname,
        3, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child default name sorted success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child default name sorted success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child default name sorted success case - got wrong child sort keys length, expected 16, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child default name sorted success case - got wrong child sort key[0], expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[1] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding second child default name sorted success case - got wrong child sort key[1], expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding third child default name sorted success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"moo", // pname,
        3, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child default name sorted success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child default name sorted success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 24)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child default name sorted success case - got wrong child sort keys length, expected 24, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child default name sorted success case - got wrong child sort key[0], expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[1] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child default name sorted success case - got wrong child sort key[1], expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[2] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding third child default name sorted success case - got wrong child sort key[2], expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // adding fourth child default name sorted success case
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"day", // pname,
        3, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding fourth child default name sorted success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding fourth child default name sorted success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 32)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding fourth child default name sorted success case - got wrong child sort keys length, expected 32, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding fourth child default name sorted success case - got wrong child sort key[0], expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[1] != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding fourth child default name sorted success case - got wrong child sort key[1], expected 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[2] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding fourth child default name sorted success case - got wrong child sort key[2], expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[3] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement adding fourth child default name sorted success case - got wrong child sort key[3], expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // testing similar words success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // making parent elementid
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"ALL", // pname,
        3, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    element1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"ALL", // pname,
        3, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"ALM", // pname,
        3, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"A", // pname,
        1, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element4 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"AO", // pname,
        2, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element5 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"AL", // pname,
        2, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element6 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"AM", // pname,
        2, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element7 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"AK", // pname,
        2, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element8 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"BK", // pname,
        2, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    element9 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid, // parentelementid,
        //1, // key,
        (unsigned char*)"B", // pname,
        1, // namelength,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking child sort keys
      // 1 = ALL
      // 2 = ALM
      // 3 = A
      // 4 = AO
      // 5 = AL
      // 6 = AM
      // 7 = AK
      // 8 = BK
      // 9 = B
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 9 * sizeof(UINT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort keys length, expected 36, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != element3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[0], expected element 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[1] != element7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[1], expected element 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[2] != element5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[2], expected element 5, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[3] != element1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[3], expected element 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[4] != element2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[4], expected element 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[5] != element6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[5], expected element 6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[6] != element4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[6], expected element 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[7] != element9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[7], expected element 9, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[8] != element8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newhlistelement testing similar words success case - got wrong child sort key[8], expected element 9, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}



void testdg_freehlistelement()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    Hlistheader myhlistheader;
    
    Hlistelementheader myhlistlementheader;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_freehlistelement\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_freehlistelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_freehlistelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement error getting hlist header array header case - got wrong error on top expected dg_freehlistelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // error getting element's header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement error getting element's header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freehlistelement (
        &BHarrayhead,
        0, // hlistheaderid,
        0); // elementheaderid)
                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_freehlistelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement error getting element's header case - got wrong error on top expected dg_freehlistelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement error getting element's header case - got wrong error 1 below top expected dg_copysfromflstrn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // freeing root success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freehlistelement (
        &BHarrayhead,
        0, // hlistheaderid,
        myelementid); // elementheaderid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got wrong name length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got wrong value length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // checking element header
    myflag = (INT64)dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid, // freeindexbuffer,
        myelementid); // flstringid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != (INT64)FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing root success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // freeing first child success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

        
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //3, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freehlistelement (
        &BHarrayhead,
        0, // hlistheaderid,
        myelementid); // elementheaderid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got wrong name length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
   
      // checking value
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got wrong value length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        myelementid,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // checking element header
    myflag = (INT64)dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid, // freeindexbuffer,
        myelementid); // flstringid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != (INT64)FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // checking parent element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        0,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing first child success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    
    // freeing default name sorted element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL freeing default name sorted element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // adding parent
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing default name sorted element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // adding first child
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"moo", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing default name sorted element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // adding second child
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"dog", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing default name sorted element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // adding third child
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"cat", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing default name sorted element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // removing middle element
    dg_freehlistelement (
        &BHarrayhead,
        0, // hlistheaderid,
        2); // elementheaderid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing default name sorted element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement freeing default name sorted element success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // checking child sort keys
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement  freeing default name sorted element success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 16)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement  freeing default name sorted element success case - got wrong child sort keys length, expected 16, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[0] != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement  freeing default name sorted element success case - got wrong child sort key[0], expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (((UINT64*)plstring)[1] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_freehlistelement  freeing default name sorted element success case - got wrong child sort key[1], expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, ((UINT64*)plstring)[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_gethlistlastchildofparent()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_gethlistlastchildofparent\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 parentelementid)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistlastchildofparentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent error getting hlist header array header case - got wrong error on top expected dg_gethlistlastchildofparentname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent error getting hlist header array header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error getting element's header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent error getting element's header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 parentelementid)

                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistlastchildofparentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent error getting element's header case - got wrong error on top expected dg_gethlistlastchildofparentname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent error getting element's header case - got wrong error 1 below top expected dg_copysfromflstrn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent error getting element's header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // no child success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent no child success case - got errors making new hlist, got:\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent no child success case - got errors making new hlist element:\n ");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }

    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 parentelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent no child success case - got errors getting last child of parent, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent no child success case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // has child success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent has child success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent has child success case - got errors making new hlist element, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //3, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent has child success case - got errors making new child hlist element, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }

    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 parentelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent has child success case - got errors getting last child of parent, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistlastchildofparent has child success case - got wrong element id, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_gethlistnextsibling()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_gethlistnextsibling\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        0, //UINT64 hlistheaderid,
        0); // UINT64 childelementid)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistnextsiblingname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling error getting hlist header array header case - got wrong error on top expected dg_gethlistlastchildofparentname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling error getting hlist header array header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error getting element's header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling error getting element's header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        0, //UINT64 hlistheaderid,
        0); // UINT64 childelementid)

                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistnextsiblingname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling error getting element's header case - got wrong error on top expected dg_gethlistlastchildofparentname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling error getting element's header case - got wrong error 1 below top expected dg_copysfromflstrn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling error getting element's header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // no next sibling success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling no next sibling success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling no next sibling success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        0, //UINT64 hlistheaderid,
        0); // UINT64 childelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling no next sibling success case - got errors getting last child of parent, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling no next sibling success case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // has next sibling child success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling has next sibling child success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling has next sibling child success case - got an error making new parent hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling has next sibling child success case - got an error making new child hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling has next sibling child success case - got an error making second new child hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        0, //UINT64 hlistheaderid,
        1); // UINT64 childelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling has next sibling child success case - got an error getting last child of parent, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistnextsibling has next sibling child success case - got wrong element id, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_gethlistprevioussibling()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_gethlistprevioussibling\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 childelementid)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistprevioussiblingname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling error getting hlist header array header case - got wrong error on top expected dg_gethlistprevioussiblingname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling error getting hlist header array header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error getting element's header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling error getting element's header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 childelementid)

                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistprevioussiblingname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling error getting element's header case - got wrong error on top expected dg_gethlistprevioussiblingname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling error getting element's header case - got wrong error 1 below top expected dg_copysfromflstrn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling error getting element's header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // no next sibling success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling no next sibling success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling no next sibling success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

     myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 childelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling no next sibling success case - got errors getting previous sibling, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling no next sibling success case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // has next sibling child success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling has next sibling child success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling has next sibling child success case - got an error making new parent hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //3, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling has next sibling child success case - got an error making new child hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //1, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling has next sibling child success case - got an error making second new child hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

     myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        2); // UINT64 childelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling has next sibling child success case - got an error getting last child of parent, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistprevioussibling has next sibling child success case - got wrong element id, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getshlistelementnom()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    UINT64 key;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getshlistelementnom\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    plstring = dg_getshlistelementnom (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getshlistelementnomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom error getting hlist header array header case - got wrong error on top expected dg_getshlistelementnomname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom error getting hlist header array header case - got wrong pointer returned, expected badbufferhandle\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error getting s of element's name lstring case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    key = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom error getting s of element's name lstring case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    plstring = dg_getshlistelementnom (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getshlistelementnomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom  error getting s of element's name lstring case - got wrong error on top expected dg_getshlistelementnomname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_elementisfreeerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom  error getting s of element's name lstring case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom error getting hlist header array header case - got wrong pointer returned, expected badbufferhandle\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //8, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    plstring = dg_getshlistelementnom (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom success case - got errors getting value, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes(plstring, lstringlength, (unsigned char*)"myname", 6, &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom success case - got an error comparing name string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom success case - name lstring didn't match, expected 'myvalue', got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)plstring); // plstring not zero terminated
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // non 0 element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom non 0 element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //8, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //8, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag2", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    plstring = dg_getshlistelementnom (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom non 0 element success case - got errors getting name, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes(plstring, lstringlength, (unsigned char*)"myname1", 7, &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom non 0 element success case - got an error comparing name string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnom non 0 element success case - tag lstring didn't match, expected 'myname1', got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)plstring); // plstring not zero terminated
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getshlistelementvalue()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    UINT64 key;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getshlistelementvalue\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    plstring = dg_getshlistelementvalue (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getshlistelementvaluename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue error getting hlist header array header case - got wrong error on top expected dg_getshlistelementvaluename, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue error getting hlist header array header case - got wrong pointer returned, expected badbufferhandle\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error getting s of element's tag lstring case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    key = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue error getting s of element's tag lstring case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    plstring = dg_getshlistelementvalue (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getshlistelementvaluename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue  error getting s of element's tag lstring case - got wrong error on top expected dg_getshlistelementvaluename, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_elementisfreeerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue  error getting s of element's tag lstring case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue error getting hlist header array header case - got wrong pointer returned, expected badbufferhandle\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //8, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    plstring = dg_getshlistelementvalue (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue success case - got errors getting value, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes(plstring, lstringlength, (unsigned char*)"myvalue", 7, &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue success case - got an error comparing name string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue success case - name lstring didn't match, expected 'myvalue', got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)plstring); // plstring not zero terminated
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // non 0 element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue non 0 element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //8, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //8, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag2", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    plstring = dg_getshlistelementvalue (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        1, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue non 0 element success case - got errors getting value, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes(plstring, lstringlength, (unsigned char*)"myvalue3", 8, &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue non 0 element success case - got an error comparing value string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue non 0 element success case - tag lstring didn't match, expected 'myvalue3', got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)plstring); // plstring not zero terminated
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}



void testdg_dobinaryinsertsortstep()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 namelstroffsetbufid;
    UINT64 namelstrstringbufid;
    
    UINT64 elementheaderlstroffsetbufid;
    UINT64 elementheaderlstrstringbufid;
    
    UINT64 sortedkeyslstroffsetbufid;
    UINT64 sortedkeyslstrstringbufid;
    
    UINT64 startindex;
    UINT64 endindex;
    UINT64 tofindbeforerangeflag;
    UINT64 loopdoneflag;
    
    UINT64 x;
    
    unsigned char* psortedkeyslstring;
    UINT64 sortedkeyslstringlength;
    
    struct CompareNameData comparedata;
    
    struct Hlistelementheader elementheader;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_dobinaryinsertsortstep\n");
    
    // success empty sort keys was greater than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0, // length,
        (unsigned char*)""); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"myname";
    comparedata.namelength = 6;
    //comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 0;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success empty success empty sort keys was greater than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was greater than case - got wrong start index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was greater than case - got wrong end index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was greater than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was greater than case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success empty sort keys was equals than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0, // length,
        (unsigned char*)""); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"myname";
    comparedata.namelength = 6;
    //comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 0;
    tofindbeforerangeflag = 0;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success empty success empty sort keys was equals case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was equals case - got wrong start index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was equals case - got wrong end index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was equals case - got wrong tofindbeforerangeflag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success success empty sort keys was equals case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success one sort key was greater than is greater than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamd"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    //dg_pushlstring (
    //    &BHarrayhead,
    //    taglstroffsetbufid,
    //    taglstrstringbufid,
    //    5, // length,
    //    (unsigned char*)"mytag"); // psrc)
    
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"myname";
    comparedata.namelength = 6;
    //comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 1;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success empty success one sort key was greater than is greater than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is greater than case - got wrong start index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is greater than case - got wrong end index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is greater than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is greater than case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success one sort key was greater than is equals case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    //dg_pushlstring (
    //    &BHarrayhead,
    //    taglstroffsetbufid,
    //    taglstrstringbufid,
    //    5, // length,
    //    (unsigned char*)"mytag"); // psrc)
    
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"myname";
    comparedata.namelength = 6;
   // comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 1;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success empty success one sort key was greater than is equals case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is equals case - got wrong start index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is equals case - got wrong end index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is equals case - got wrong tofindbeforerangeflag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is equals case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success one sort key was greater than is less than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    //dg_pushlstring (
    //    &BHarrayhead,
    //    taglstroffsetbufid,
    //    taglstrstringbufid,
    //    5, // length,
    //    (unsigned char*)"mytag"); // psrc)
    
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"mynamd";
    comparedata.namelength = 6;
    //comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 1;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success empty success one sort key was greater than is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is less than case - got wrong start index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is less than case - got wrong end index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success one sort key was greater than is less than case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success two sort keys was greater than is greater than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
    
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"mynamh";
    comparedata.namelength = 6;
    //comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 2;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong end index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    // success two sort keys was greater than is equal case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
    
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"mynamg";
    comparedata.namelength = 6;
    //comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 2;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is equal case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is equal case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is equal case - got wrong end index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is equal case - got wrong tofindbeforerangeflag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is equal case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success two sort keys was greater than is less than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    //taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
    
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    //comparedata.ptag = (unsigned char*)"mytag";
    //comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"mynamf";
    comparedata.namelength = 6;
    //comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    //comparedata.taglstroffsetbufid = taglstroffsetbufid;
    //comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 2;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong start index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong end index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was greater than is less than case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success two sort keys was equals is greater than case
      // techically this means your sort keys are out of order
      // you should only get less than or equals after the compare
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
            
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamh";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    
    startindex = 0;
    endindex = 2;
    tofindbeforerangeflag = 0;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is greater than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is greater than case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is greater than case - got wrong end index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is greater than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is greater than case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success two sort keys was equals is equal case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamg";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
   
    startindex = 0;
    endindex = 2;
    tofindbeforerangeflag = 0;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is equal case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is equal case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals equal case - got wrong end index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is equal case - got wrong tofindbeforerangeflag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is equal case - got wrong loop done flag, expected FORTH_TRUE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success two sort keys was equals is less than case
      // need to go back and check first element in rage
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamf";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    
    startindex = 0;
    endindex = 2;
    tofindbeforerangeflag = 0;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is less than case - got wrong start index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is less than case - got wrong end index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success two sort keys was equals is less than case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success three sort keys was greater than is greater than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynami"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
    
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=2;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamh";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    
    startindex = 0;
    endindex = 3;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong end index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success two sort keys was greater than is equal case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynami"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)

    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=2;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamg";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    
    startindex = 0;
    endindex = 3;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is equal case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is equal case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is equal case - got wrong end index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is equal case - got wrong tofindbeforerangeflag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is equal case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success three sort keys was greater than is less than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynami"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)

    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=2;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamf";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    
    startindex = 0;
    endindex = 3;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong start index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong end index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was greater than is less than case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success three sort keys was equals is greater than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynami"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)

    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=2;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamh";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    
    startindex = 0;
    endindex = 3;
    tofindbeforerangeflag = 0;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong end index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success two sort keys was equals is equal case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
    //elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynami"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)

    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=2;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
//    comparedata.ptag = (unsigned char*)"mytag";
//    comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"mynamg";
    comparedata.namelength = 6;
//    comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
//    comparedata.taglstroffsetbufid = taglstroffsetbufid;
//    comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 3;
    tofindbeforerangeflag = 0;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is equal case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is equal case - got wrong start index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is equal case - got wrong end index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is equal case - got wrong tofindbeforerangeflag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is equal case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success three sort keys was equals is less than case
      // sort keys out of order case - I should make this an error
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
//    taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
//    taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
//    elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynami"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
 
    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=2;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
//    comparedata.ptag = (unsigned char*)"mytag";
//    comparedata.taglength = 5;
    comparedata.pname = (unsigned char*)"mynamf";
    comparedata.namelength = 6;
//    comparedata.key = 3;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
//    comparedata.taglstroffsetbufid = taglstroffsetbufid;
//    comparedata.taglstrstringbufid = taglstrstringbufid;
    
    startindex = 0;
    endindex = 3;
    tofindbeforerangeflag = 0;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong start index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong end index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong tofindbeforerangeflag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success three sort keys was equals is less than case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success four sort keys first not zero was greater than is less than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    namelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    namelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    elementheaderlstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
//    taglstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
//    taglstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    sortedkeyslstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 10000, &pError, FORTH_FALSE);
    
    elementheader.magic = dg_hlistelementmagic;                        // 'hlel'
    elementheader.parentelementid = DG_ENDOFLIST;
    elementheader.lastchildelementid = DG_ENDOFLIST; 
    elementheader.nextsiblingelementid = DG_ENDOFLIST;
    elementheader.previoussiblingelementid = DG_ENDOFLIST;
//    elementheader.key = 3;
    
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"myname"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamg"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynami"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamk"); // psrc)

    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynaml"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        namelstroffsetbufid,
        namelstrstringbufid,
        6, // length,
        (unsigned char*)"mynamn"); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)
        
    dg_pushlstring (
        &BHarrayhead,
        elementheaderlstroffsetbufid,
        elementheaderlstrstringbufid,
        sizeof(Hlistelementheader), // length,
        (unsigned char*)&elementheader); // psrc)

    x=0;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=1;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=2;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=3;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=4;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
        
    x=5;
    
    dg_pushlstring (
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        sizeof(UINT64), // length,
        (unsigned char*)&x); // psrc)
    
    psortedkeyslstring = dg_getplstring(
        &BHarrayhead,
        sortedkeyslstroffsetbufid,
        sortedkeyslstrstringbufid,
        0,
        &sortedkeyslstringlength);
            
    comparedata.pname = (unsigned char*)"mynamj";
    comparedata.namelength = 6;
    comparedata.namelstroffsetbufid = namelstroffsetbufid;
    comparedata.namelstrstringbufid = namelstrstringbufid;
    comparedata.elementheaderlstroffsetbufid = elementheaderlstroffsetbufid;
    comparedata.elementheaderlstrstringbufid = elementheaderlstrstringbufid;
    
    startindex = 1;
    endindex = 5;
    tofindbeforerangeflag = 1;
    loopdoneflag = FORTH_FALSE;

    dg_dobinaryinsertsortstep (
        &BHarrayhead,
        psortedkeyslstring,
        sortedkeyslstringlength,
        &dg_sortcomparehlistnom,
        (void*)(&comparedata),
        sizeof(CompareNameData),
        &startindex,
        &endindex,
        &tofindbeforerangeflag,
        &loopdoneflag);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success four sort keys first not zero was greater than is less than case - got an error doing dg_dobinaryinsertsortstep, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (startindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success four sort keys first not zero was greater than is less than case - got wrong start index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, startindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (endindex != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success four sort keys first not zero was greater than is less than case - got wrong end index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, endindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindbeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success four sort keys first not zero was greater than is less than case - got wrong tofindbeforerangeflag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindbeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (loopdoneflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! success four sort keys first not zero was greater than is less than case - got wrong loop done flag, expected FORTH_FALSE, got ");
        dg_writestdoutuinttodec(&BHarrayhead, loopdoneflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_findsortedhlistchild()
{
    Bufferhandle BHarrayhead;
    
    UINT64 keyofvaluetofind;
    UINT64 hlistheaderid;
    UINT64 parentelementid;
    UINT64 childelementid1, childelementid2, childelementid3, childelementid4, childelementid5;
    
    UINT64 indexofkeyaftermatch;  // index in sort key lstring after match
    UINT64 foundkey;              // key = f[indexaftermatch - 1]
    
    UINT64 tofindtobeforerangeflag;
    
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_findsortedhlistchild\n");
    
    //  Bad memory at pindexofkeyaftermatch case
    dg_initbuffers(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = 0;
    parentelementid = 0;
    
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        hlistheaderid, 
        parentelementid,
        ((UINT64*)(-2)), // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
  
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_findsortedhlistchildname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Bad memory at pindexofkeyaftermatch case - got wrong error on top, expected dg_findsortedhlistchildname, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);  
    
    if (pError != dg_putuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Bad memory at pindexofkeyaftermatch case - got wrong error 1 below top, expected dg_putUINT64name, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Bad memory at pindexofkeyaftermatch case - got wrong error 2 below top, expected dg_badmemoryerror, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    //  Bad memory at pfoundkey case
    dg_initbuffers(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = 0;
    parentelementid = 0;
    
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        ((UINT64*)(-2))); // key = f[indexaftermatch - 1]
  
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_findsortedhlistchildname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Bad memory at pfoundkey case - got wrong error on top, expected dg_findsortedhlistchildname, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);  
    
    if (pError != dg_putuint64name)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Bad memory at pfoundkey case - got wrong error 1 below top, expected dg_putuint64name, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Bad memory at pfoundkey case - got wrong error 2 below top, expected dg_badmemoryerror, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
        
    //  error getting hlist header case
    dg_initbuffers(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = 0;
    parentelementid = 0;
    
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
  
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_findsortedhlistchildname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild error getting hlist header case - got wrong error on top, expected dg_findsortedhlistchildname, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);  
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild error getting hlist header case - got wrong error 1 below top, expected dg_gethlistheadername, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    //  error getting hlist element header freeable lstring header case
    //  if get hlist header worked, this should work too
    
    //  error getting pointer and length of sorted keys lstring case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    parentelementid = 0;
    
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
  
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_findsortedhlistchildname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild error getting pointer and length of sorted keys lstring case - got wrong error on top, expected dg_findsortedhlistchildname, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);  
    
    if (pError != dg_sortedkeyslstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild error getting pointer and length of sorted keys lstring case - got wrong error 1 below top, expected dg_copyflstrheadertosname, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);  
    
    if (pError != dg_getplstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild error getting pointer and length of sorted keys lstring case - got wrong error 1 below top, expected dg_copyflstrheadertosname, got: ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // misaligned sorted child element ids lstring case
    
    //  Success case empty sorted index list
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"myparentname",
        12,
        (unsigned char*)"myparentvalue",
        13);
    
    
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild misaligned sorted child element ids lstring case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild misaligned sorted child element ids lstring case - got wrong index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild misaligned sorted child element ids lstring case - got wrong foundkey, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != (UINT64)(-2))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild misaligned sorted child element ids lstring case - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success 1 item list equal case
    //  should be manually building the sort key list
    //  probably should be building the hlist manually too
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"myparentname",
        12,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"myname",
        6,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list equal case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list equal case - got wrong index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list equal case - got wrong found key, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list equal case - got wrong result flag, expected 0 for equal, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success 1 item list greater than case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)"myparentname",
        12,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"mynamd", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list greater than case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list greater than case - got wrong index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list greater than case - got wrong found key, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 1 item list greater than case - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success 2 item list equals last case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamd",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list equals last case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list equals last case - got wrong index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list equals last case - got wrong found key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list equals last case - got wrong result flag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    // success 2 item list equals first case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamf",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list equals first case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list equals first case - got wrong index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list equals first case - got wrong found key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchildsuccess 2 item list equals first case - got wrong result flag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success 2 item list less than all case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamg",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamf",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list less than all case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list less than all case - got wrong index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list less than all case - got wrong found key, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list less than all case - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success 2 item list between middle case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamd",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamf",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list between middle case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list between middle case - got wrong index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list between middle case - got wrong found key, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list between middle case - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success 2 item list after all case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamc",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamd",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list after all case - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list after all case - got wrong index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list after all case - got wrong found key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild success 2 item list after all case - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    //  Success case equals middle of 3
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamc",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamg",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equals middle of 3 - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equals middle of 3 - got wrong index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equals middle of 3 - got wrong found key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equals middle of 3 - got wrong result flag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    //  Success case between 2 of 3
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamc",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamd",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamg",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case between 2 of 3 - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case between 2 of 3 - got wrong index, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case between 2 of 3 - got wrong found key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case between 2 of 3 - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    //  Success case less than all of 3
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamz",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamx",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamy",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case less than all of 3 - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case less than all of 3 - got wrong index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case less than all of 3 - got wrong found key, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case less than all of 3 - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    
    dg_freeallbuffers(&BHarrayhead);

    
    //  Success case greater than all of 3
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynama",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamb",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamc",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case greater than all of 3 - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case greater than all of 3 - got wrong index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case greater than all of 3 - got wrong found key, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case greater than all of 3 - got wrong result flag, expected 1 for greater than, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    //  Success case equal last of 3
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynama",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamb",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal last of 3 - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal last of 3 - got wrong index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal last of 3 - got wrong found key, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal last of 3 - got wrong result flag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);

    
    //  Success case equal first of 3
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamh",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamf",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal first of 3 - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal first of 3 - got wrong index, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal first of 2 - got wrong found key, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case equal first of 3 - got wrong result flag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    //  Success case multiple equal in middle
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamd",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid4 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid5 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamf",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle - got wrong index, expected 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle - got wrong found key, expected 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle - got wrong result flag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // Success case multiple equal in middle 2
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    keyofvaluetofind = 5;
    hlistheaderid = dg_newhlist(&BHarrayhead);
    
    parentelementid = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        DG_ENDOFLIST, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //3,            // key
        (unsigned char*)"myparentname",
        12,
        //(unsigned char*)"myparenttag",
        //11,
        (unsigned char*)"myparentvalue",
        13);
        
    childelementid1 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamd",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid2 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid3 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamg",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid4 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"myname",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    childelementid5 = dg_newhlistelement (
        &BHarrayhead,
        hlistheaderid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7,               // key
        (unsigned char*)"mynamf",
        6,
        //(unsigned char*)"mytag",
        //5,
        (unsigned char*)"mychildvalue1",
        14);
        
    // current default newhlistelement sort is name sorted
    tofindtobeforerangeflag = dg_findsortedhlistchild (
        &BHarrayhead,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //7, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
        hlistheaderid, 
        parentelementid,
        &indexofkeyaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundkey); // key = f[indexaftermatch - 1]
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle 2 - got an error, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
    }
    
    if (indexofkeyaftermatch != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle 2 - got wrong index, expected 3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, indexofkeyaftermatch);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundkey != childelementid4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle 2 - got wrong found key, expected 4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundkey);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tofindtobeforerangeflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_findsortedhlistchild Success case multiple equal in middle 2 - got wrong result flag, expected 0 for equals, got ");
        dg_writestdoutuinttodec(&BHarrayhead, tofindtobeforerangeflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_newunsortedhlistelement()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    UINT64 element1;
    
    UINT64 x;
    
    Hlistheader myhlistheader;
    
    Hlistelementheader myhlistlementheader;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newunsortedhlistelement\n");
    
    // adding new unsorted element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        0,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting copy of hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error making root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
        
    element1 = dg_newunsortedhlistelement (
        &BHarrayhead,
        0,
        myhlistheader,
        myelementid, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        //7, // key,
        (unsigned char*)"myunsortedname", // pname,
        14, // namelength,
        //(unsigned char*)"myunsortedtag", // ptag,
        //13, // taglength,
        (unsigned char*)"myunsortedvalue", // pvalue,
        15, // valuelength,
        6, // previouselementid,
        8); //nextelementid)

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error making new unsorted hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting hlist header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

      // checking name
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting number of name lstrings, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != element1 + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong number of name lstrings, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        element1,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting pointer to name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 14)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong name length, expected 14, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        14,
        (unsigned char*)"myunsortedname",
        14,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error comparing name lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - name lstring wrong, expected 'myname', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

   
      // checking value
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting number of value lstrings, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != element1 + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong number of value lstrings, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        element1,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting pointer to value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 15)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong value length, expected 15, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        15,
        (unsigned char*)"myunsortedvalue",
        15,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error comparing value lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - value lstring wrong, expected 'myvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)plstring);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


      // checking child sort keys
    x = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting number of child sort keys lstrings, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (x != element1 + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong number of child sort keys lstrings, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        element1,
        &lstringlength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting pointer to child sort keys lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong child sort keys length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // checking element header
    dg_copysfromflstrn(
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        element1,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistlementheader);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got an error getting element header, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.magic != dg_hlistelementmagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong magic, expected hlistelementmagic, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.magic);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.parentelementid != myelementid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong parent, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.parentelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.lastchildelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong last child, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.lastchildelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.nextsiblingelementid != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong next sibling, expected 8, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.nextsiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myhlistlementheader.previoussiblingelementid != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong previous sibling, expected 6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.previoussiblingelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    //if (myhlistlementheader.key != 7)
    //{
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_newunsortedhlistelement  adding new unsorted element success case - got wrong key, expected 7, got ");
    //    dg_writestdoutuinttodec(&BHarrayhead, myhlistlementheader.key);
    //    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    //}
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_gethlistelementparent()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid, myelementid1, myelementid2, myelementid3;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_gethlistelementparent\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    myelementid = dg_gethlistelementparent (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 childelementid)
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistelementparentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent error getting hlist header array header case - got wrong error on top expected dg_gethlistelementparentname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent error getting hlist header array header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error getting element's header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent error getting element's header case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myelementid = dg_gethlistelementparent (
        &BHarrayhead,
        0, // UINT64 hlistheaderid,
        0); // UINT64 childelementid)

                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistelementparentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent error getting element's header case - got wrong error on top expected dg_gethlistprevioussiblingname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent error getting element's header case - got wrong error 1 below top expected dg_copysfromflstrn, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent error getting element's header case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // no parent success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent no next sibling success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent no next sibling success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

     myelementid1 = dg_gethlistelementparent (
        &BHarrayhead,
        myhlistid, // UINT64 hlistheaderid,
        myelementid); // UINT64 childelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent no next sibling success case - got errors getting previous sibling, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    if (myelementid1 != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent no next sibling success case - got wrong element id, expected DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // has parent success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent has next sibling child success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //1, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent has next sibling child success case - got an error making new parent hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        //3, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag1", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent has next sibling child success case - got an error making new child hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
     myelementid3 = dg_gethlistelementparent (
        &BHarrayhead,
        myhlistid, // UINT64 hlistheaderid,
        myelementid2); // UINT64 childelementid)
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent has next sibling child success case - got an error getting last child of parent, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myelementid3 != myelementid1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_gethlistelementparent has next sibling child success case - got wrong element id, expected 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid3);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_sethlistelementvalue()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    UINT64 key;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_sethlistelementvalue\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
    
    dg_sethlistelementvalue (
        &BHarrayhead,
        0, // hlistheaderid,
        0, // elementid,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_sethlistelementvaluename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue error getting hlist header array header case - got wrong error on top expected dg_sethlistelementvaluename, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue error getting hlist header array header case - got wrong error 1 below top expected dg_gethlistheadername, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // error replacing lstring case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    key = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue error getting s of element's tag lstring case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_sethlistelementvalue (
        &BHarrayhead,
        0, // hlistheaderid,
        0, // elementid,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
                
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_sethlistelementvaluename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue  error getting s of element's tag lstring case - got wrong error on top expected dg_sethlistelementvaluename, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_elementisfreeerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue  error getting s of element's tag lstring case - got wrong error 1 below top expected dg_getplstringname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //8, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_sethlistelementvalue (
        &BHarrayhead,
        myhlistid, // hlistheaderid,
        myelementid, // elementid,
        (unsigned char*)"giraffes", // pvalue,
        8); // valuelength);
                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue  success case - got error setting hlist value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    plstring = dg_getshlistelementvalue (
        &BHarrayhead,
        myhlistid, // UINT64 hlistheaderid,
        myelementid, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementvalue success case - got errors getting value, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes(plstring, lstringlength, (unsigned char*)"giraffes", 8, &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue success case - got an error comparing name string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue success case - name lstring didn't match, expected 'giraffes', got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)plstring); // plstring not zero terminated
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // non 0 element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue non 0 element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //8, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //8, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag2", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_sethlistelementvalue (
        &BHarrayhead,
        myhlistid, // hlistheaderid,
        myelementid, // elementid,
        (unsigned char*)"giraffes", // pvalue,
        8); // valuelength);
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue non 0 element success case - got errors setting value, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }

    plstring = dg_getshlistelementvalue (
        &BHarrayhead,
        myhlistid, // UINT64 hlistheaderid,
        myelementid, // UINT64 elementid,
        &lstringlength); // UINT64* ptaglength)
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue non 0 element success case - got errors getting value, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes(plstring, lstringlength, (unsigned char*)"giraffes", 8, &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue non 0 element success case - got an error comparing value string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sethlistelementvalue non 0 element success case - tag lstring didn't match, expected 'giraffes', got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)plstring); // plstring not zero terminated
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
   
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getshlistelementnamene()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getshlistelementnamene\n");
    
    //  error getting hlist header array header case
    dg_initbuffers(&BHarrayhead);
        
    pError = dg_getshlistelementnamene (
        &BHarrayhead,
        0, // hlistheaderid,
        0, // elementid,
        &plstring, // unsigned char** ppname,
        &lstringlength); // UINT64* pnamelength)
        
    if (pError != dg_errorinsubroutine)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene error getting hlist header array header case - got wrong error returned, expected dg_getshlistelementnomname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene error getting hlist header array header case - got wrong error on top, expected dg_getshlistelementnomname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene error getting hlist header array header case - got wrong pointer returned, expected badbufferhandle\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    

    // non 0 element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene non 0 element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        //8, // key,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        //(unsigned char*)"mytag", // ptag,
        //5, // taglength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        //8, // key,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        //(unsigned char*)"mytag2", // ptag,
        //6, // taglength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pError = dg_getshlistelementnamene (
        &BHarrayhead,
        myhlistid, // hlistheaderid,
        myelementid, // elementid,
        &plstring, // unsigned char** ppname,
        &lstringlength); // UINT64* pnamelength)
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene error getting hlist header array header case - got wrong error returned, expected dg_success, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene non 0 element success case - got errors getting name, got:\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_clearerrors(&BHarrayhead);
    }
    
    pError = dg_comparebytes(plstring, lstringlength, (unsigned char*)"myname1", 7, &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene non 0 element success case - got an error comparing name string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getshlistelementnamene non 0 element success case - tag lstring didn't match, expected 'myname1', got ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)plstring); // plstring not zero terminated
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_sortcomparehlistnom()
{
    Bufferhandle BHarrayhead;
    
    INT64 compareFlag;
    struct CompareNameData mydata;
    
    UINT64 keyofmidrangevalue;
    
    UINT64 mynamelstroffsetbufid;
    UINT64 mynamelstrstringbufid;
    
    const char* pError;
        
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_sortcomparehlistnom\n");
    
    //  error accessing lstring array case
    dg_initbuffers(&BHarrayhead);
    
    mydata.pname = (unsigned char*)"myname";
    mydata.namelength = 6;
    mydata.namelstroffsetbufid = (UINT64)dg_badbufferid;
    mydata.namelstrstringbufid = (UINT64)dg_badbufferid;
    keyofmidrangevalue = 0;
        
    compareFlag = dg_sortcomparehlistnom(
        &BHarrayhead,
        (void*)&mydata,           // pcomparedata,
        sizeof(CompareNameData),  // comparedatalength,
        keyofmidrangevalue);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_sortcomparehlistnomname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sortcomparehlistnom error accessing lstring array case - got wrong error returned, expected dg_sortcomparehlistnomname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareFlag != -2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sortcomparehlistnom error accessing lstring array case - got wrong compare flag returned\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    

    // non 0 element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mynamelstroffsetbufid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);
    mynamelstrstringbufid = dg_newbuffer(&BHarrayhead, 1000, 5000, &pError, FORTH_FALSE);
    
    dg_pushlstring (
        &BHarrayhead,
        mynamelstroffsetbufid, // offsetbufferid,
        mynamelstrstringbufid, // stringbufferid,
        7, // length,
        (unsigned char*)"myname0"); // psrc);
    
    dg_pushlstring (
        &BHarrayhead,
        mynamelstroffsetbufid, // offsetbufferid,
        mynamelstrstringbufid, // stringbufferid,
        7, // length,
        (unsigned char*)"myname1"); // psrc);
    
    dg_pushlstring (
        &BHarrayhead,
        mynamelstroffsetbufid, // offsetbufferid,
        mynamelstrstringbufid, // stringbufferid,
        7, // length,
        (unsigned char*)"myname2"); // psrc);
    
    mydata.pname = (unsigned char*)"myname2";
    mydata.namelength = 7;
    mydata.namelstroffsetbufid = mynamelstroffsetbufid;
    mydata.namelstrstringbufid = mynamelstrstringbufid;
    keyofmidrangevalue = 2;
        
    compareFlag = dg_sortcomparehlistnom(
        &BHarrayhead,
        (void*)&mydata,           // pcomparedata,
        sizeof(CompareNameData),  // comparedatalength,
        keyofmidrangevalue);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sortcomparehlistnom non 0 element success case - got an error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (compareFlag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_sortcomparehlistnom non 0 element success case - got wrong compare flag returned\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getidofsortedhlistchildn()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myid;
    UINT64 myhlistid;
    UINT64 myrootelementid;
    UINT64 mychildelementid1;
    UINT64 mychildelementid2;
    UINT64 mychildelementid3;
        
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getidofsortedhlistchildn\n");
    
    //  error getting hlist header case
    dg_initbuffers(&BHarrayhead);
    
    myid = dg_getidofsortedhlistchildn(
        &BHarrayhead,
        0, // hlistheaderid,
        0, // parentelementid,
        0); // sortkeyindex)    
        
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getidofsortedhlistchildnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname error getting hlist header case - got wrong error returned, expected dg_sortcomparehlistnomname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myid != (UINT64)DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname error getting hlist header case - got wrong child element returned\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    

    // non 0 element success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myrootelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myrootname", // pname,
        10, // namelength,
        (unsigned char*)"myrootvalue", // pvalue,
        11); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mychildelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myrootelementid, // parentelementid,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mychildelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myrootelementid, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mychildelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myrootelementid, // parentelementid,
        (unsigned char*)"myname3", // pname,
        7, // namelength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myid = dg_getidofsortedhlistchildn(
        &BHarrayhead,
        myhlistid, // hlistheaderid,
        myrootelementid, // parentelementid,
        1); // sortkeyindex)    
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case - got an error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myid != mychildelementid2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case - got wrong child element returned\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
    
    // non 0 element success case 2
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case 2 - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myrootelementid = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myrootname", // pname,
        10, // namelength,
        (unsigned char*)"myrootvalue", // pvalue,
        11); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mychildelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myrootelementid, // parentelementid,
        (unsigned char*)"myname3", // pname,
        7, // namelength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mychildelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myrootelementid, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    mychildelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myrootelementid, // parentelementid,
        (unsigned char*)"myname1", // pname,
        7, // namelength,
        (unsigned char*)"myvalue1", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myid = dg_getidofsortedhlistchildn(
        &BHarrayhead,
        myhlistid, // hlistheaderid,
        myrootelementid, // parentelementid,
        2); // sortkeyindex)    
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case 2 - got an error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myid != mychildelementid1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getidofsortedhlistchildnname non 0 element success case 2 - got child element returned\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_addnsamechartostring()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 n;
    unsigned char c;
    
    unsigned char* plstring;
    UINT64 lstringlength;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_addnsamechartostring\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // dg_forthnewstring(&BHarrayhead);
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // stringbufferid,
        0, // length,
        (unsigned char*)"");
    
    n=5;
    c='z';
    
    INT64 myflag;
    
    dg_addnsamechartostring (
        &BHarrayhead,
        n,
        c);
           
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_addnsamechartostring success case - got an error, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID,
        0, // stringid
        &lstringlength);
        
    if (lstringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_addnsamechartostring success case - got wrong length.\n");
    }
    
    pError = dg_comparebytes (
        (unsigned char*)plstring, 
        lstringlength,
        (unsigned char*)"zzzzz",
        5,
		&myflag);
        
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_addnsamechartostring success case - string didn't match.\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}


void testdg_changehlistelementparent()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    UINT64 myelementid1;
    UINT64 myelementid2;
    UINT64 myelementid3;
    UINT64 myelementid4;
    UINT64 myelementid5;
    UINT64 myelementid6;
    
    UINT64 numberofchildren;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_changehlistelementparent\n");
    
    // error getting hlist header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_changehlistelementparent (
        &BHarrayhead,
        0, // hlistid,
        0, // elementid,
        DG_ENDOFLIST); // newparentelementid)
    
    pError = dg_poperror(&BHarrayhead);
                                                
    if (pError != dg_changehlistelementparentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent error getting hlist header case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
                                                
    if (pError != dg_gethlistheadername)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent error getting hlist header case - got wrong error one below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // error getting element's header case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent error getting element's header case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_changehlistelementparent (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // elementid,
        DG_ENDOFLIST); // newparentelementid)
    
    pError = dg_poperror(&BHarrayhead);
                                                
    if (pError != dg_changehlistelementparentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent error getting hlist header case - got wrong error on top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
                                                
    if (pError != dg_copysfromflstrnname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent error getting hlist header case - got wrong error one below top, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // remove parent success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparentremove parent success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent remove parent success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent remove parent success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_changehlistelementparent (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid2, // elementid,
        DG_ENDOFLIST); // newparentelementid)
                                                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent remove parent success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistelementparent (
        &BHarrayhead,
        myhlistid, // UINT64 hlistheaderid,
        myelementid2); // UINT64 childelementid)
        
    if (myelementid != (UINT64)DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent remove parent success case - element's new parent value wrong, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // change parent success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname3", // pname,
        7, // namelength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_changehlistelementparent (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid2, // elementid,
        myelementid3); // newparentelementid)
                                                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistelementparent (
        &BHarrayhead,
        myhlistid, // UINT64 hlistheaderid,
        myelementid2); // UINT64 childelementid)
        
    if (myelementid != myelementid3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case - element's new parent value wrong, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        myhlistid,
        myelementid1);
        
    if (myelementid != (UINT64)DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case - old parent's last child wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // change parent success case 2
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname3", // pname,
        7, // namelength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid4 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname4", // pname,
        7, // namelength,
        (unsigned char*)"myvalue4", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid5 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname5", // pname,
        7, // namelength,
        (unsigned char*)"myvalue5", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid6 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid5, // parentelementid,
        (unsigned char*)"myname6", // pname,
        7, // namelength,
        (unsigned char*)"myvalue6", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_changehlistelementparent (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid3, // elementid,
        myelementid5); // newparentelementid)
                                                
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistelementparent (
        &BHarrayhead,
        myhlistid, // UINT64 hlistheaderid,
        myelementid3); // UINT64 childelementid)
        
    if (myelementid != myelementid5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - element's new parent value wrong, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        myhlistid,
        myelementid1);
        
    if (myelementid != myelementid4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's last child wrong, should be myelementid4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        myhlistid,
        myelementid4);
        
    if (myelementid != myelementid2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's latest child's previous sibling wrong, should be myelementid2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        myhlistid,
        myelementid4);
        
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's latest child's next sibling wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        myhlistid,
        myelementid2);
        
    if (myelementid != (UINT64)DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's 2nd latest child's previous sibling wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        myhlistid,
        myelementid2);
        
    if (myelementid != myelementid4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's 2nd latest child's next sibling wrong, should be myelementid4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        myhlistid,
        myelementid5);
        
    if (myelementid != myelementid3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's last child wrong, should be myelementid5, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        myhlistid,
        myelementid3);
        
    if (myelementid != myelementid6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's last child's previous sibling wrong, should be myelementid6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        myhlistid,
        myelementid3);
        
    if (myelementid != (UINT64)DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's last child's next sibling wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistprevioussibling (
        &BHarrayhead,
        myhlistid,
        myelementid6);
        
    if (myelementid != (UINT64)DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's 2nd latest child's previous sibling wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistnextsibling (
        &BHarrayhead,
        myhlistid,
        myelementid6);
        
    if (myelementid != myelementid3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's 2nd latest child's next sibling wrong, should be myelement6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    numberofchildren = dg_getnumberofsortedchildren(
        &BHarrayhead,
        myhlistid,
        myelementid1);
        
    if (numberofchildren != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's number of sorted children wrong, should be 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, numberofchildren);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_getidofsortedhlistchildn(
        &BHarrayhead,
        myhlistid,
        myelementid1,
        0);
        
    if (myelementid != myelementid2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's sorted child[0] wrong, should be myelementid2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, numberofchildren);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_getidofsortedhlistchildn(
        &BHarrayhead,
        myhlistid,
        myelementid1,
        1);
        
    if (myelementid != myelementid4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - old parent's sorted child[1] wrong, should be myelementid4, got ");
        dg_writestdoutuinttodec(&BHarrayhead, numberofchildren);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    numberofchildren = dg_getnumberofsortedchildren(
        &BHarrayhead,
        myhlistid,
        myelementid5);
        
    if (numberofchildren != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's number of sorted children wrong, should be 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, numberofchildren);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_getidofsortedhlistchildn(
        &BHarrayhead,
        myhlistid,
        myelementid5,
        0);
        
    if (myelementid != myelementid3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's sorted child[0] wrong, should be myelementid3, got ");
        dg_writestdoutuinttodec(&BHarrayhead, numberofchildren);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_getidofsortedhlistchildn(
        &BHarrayhead,
        myhlistid,
        myelementid5,
        1);
        
    if (myelementid != myelementid6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_changehlistelementparent change parent success case 2 - new parent's sorted child[1] wrong, should be myelementid6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, numberofchildren);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_prunehlistelement()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    UINT64 myelementid;
    
    UINT64 myelementid1;
    UINT64 myelementid2;
    UINT64 myelementid3;
    UINT64 myelementid4;
    UINT64 myelementid5;
    UINT64 myelementid6;
    UINT64 myelementid7;
    
    UINT64 myflag;
    
    Hlistheader myhlistheader;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_prunehlistelement\n");
    
    // trying to prune free element error case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement trying to prune free element error case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement trying to prune free element error case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement trying to prune free element error case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freehlistelement (
        &BHarrayhead,
        myhlistid, // hlistheaderid,
        myelementid1); // elementheaderid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement trying to prune free element error case - got an error freeing hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_prunehlistelement (
        &BHarrayhead,
        myhlistid,
        myelementid1);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_prunehlistelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement trying to prune free element error case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_gethlistlastchildofparentname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement trying to prune free element error case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // no children success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname3", // pname,
        7, // namelength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_prunehlistelement (
        &BHarrayhead,
        myhlistid,
        myelementid2);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        myhlistid,
        myelementid2);
        
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - second parent's last child wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // get the hlist header 
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - error getting hlist header\n");
    }
    
    myflag = dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - error checking free status of element 2\n");
    }
    
    if (myflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - element 1 was freed.\n");
    }
    
    myflag = dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid3);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - error checking free status of element 3\n");
    }
    
    if (myflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement no children success case - element 3 was freed.\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success case 2
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname3", // pname,
        7, // namelength,
        (unsigned char*)"myvalue3", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid4 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"myname4", // pname,
        7, // namelength,
        (unsigned char*)"myvalue4", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid5 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid3, // parentelementid,
        (unsigned char*)"myname5", // pname,
        7, // namelength,
        (unsigned char*)"myvalue5", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid6 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid3, // parentelementid,
        (unsigned char*)"myname6", // pname,
        7, // namelength,
        (unsigned char*)"myvalue6", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid7 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname7", // pname,
        7, // namelength,
        (unsigned char*)"myvalue7", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_prunehlistelement (
        &BHarrayhead,
        myhlistid,
        myelementid1);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        myhlistid,
        myelementid1);
        
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - first parent's last child wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // making sure element not under parent is left alone
    myelementid = dg_gethlistlastchildofparent (
        &BHarrayhead,
        myhlistid,
        myelementid7);
        
    if (myelementid != DG_ENDOFLIST)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - extra parent's last child wrong, should be DG_ENDOFLIST, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myelementid);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
      // get the hlist header 
    dg_gethlistheader(
        &BHarrayhead,
        myhlistid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - error getting hlist header\n");
    }
    
    myflag = dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid2);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - error checking free status of element 2\n");
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - element 2 was not freed.\n");
    }
    
    myflag = dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid3);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - error checking free status of element 3\n");
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - element 3 was not freed.\n");
    }
    
    myflag = dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid4);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - error checking free status of element 4\n");
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - element 4 was not freed.\n");
    }
    
    myflag = dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid5);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - error checking free status of element 5\n");
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - element 5 was not freed.\n");
    }
    
    myflag = dg_isfreeablelstringfree (
        &BHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        myelementid6);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - error checking free status of element 6\n");
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_prunehlistelement success case 2 - element 6 was not freed.\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_hlisttodglumlstring()
{
    Bufferhandle BHarrayhead;
    
    const char* pError;
    
    UINT64 myhlistid;
    
    UINT64 myelementid1;
    UINT64 myelementid2;
    UINT64 myelementid3;
    UINT64 myelementid4;
    
    UINT64 stringstackdepth;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    INT64 compareflag;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_hlisttodglumlstring\n");
    
    // trying to convert free element error case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname", // pname,
        6, // namelength,
        (unsigned char*)"myvalue", // pvalue,
        7); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"myname2", // pname,
        7, // namelength,
        (unsigned char*)"myvalue2", // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_freehlistelement (
        &BHarrayhead,
        myhlistid, // hlistheaderid,
        myelementid1); // elementheaderid)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got an error freeing hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // dg_forthnewstring(&BHarrayhead);
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // stringbufferid,
        0, // length,
        (unsigned char*)"");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got an error making new string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_hlisttodglumlstring (
        &BHarrayhead,
        myhlistid,
        myelementid1,
        2, // indentationstepsize,
        0); // currentindentationlevel);
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_hlisttodglumlstringname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got wrong error on top, expected dg_hlisttodglumlstringname got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_getshlistelementname)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got wrong error 1 below top, expected dg_getshlistelementname, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_poperror(&BHarrayhead);
    
    if (pError != dg_elementisfreeerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring trying to convert free element error case - got wrong error 2 below top, expected dg_elementisfreeerror, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid1 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"root", // pname,
        4, // namelength,
        (unsigned char*)"myrootvalue", // pvalue,
        11); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid2 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"element2", // pname,
        8, // namelength,
        (unsigned char*)"myelementvalue2", // pvalue,
        15); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid3 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        (unsigned char*)"element3", // pname,
        8, // namelength,
        (unsigned char*)"myelementvalue3", // pvalue,
        15); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myelementid4 = dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid2, // parentelementid,
        (unsigned char*)"element4", // pname,
        8, // namelength,
        (unsigned char*)"myelementvalue4", // pvalue,
        15); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error making new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // dg_forthnewstring(&BHarrayhead);
    dg_pushlstring (
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // stringbufferid,
        0, // length,
        (unsigned char*)"");
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error making new string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_hlisttodglumlstring (
        &BHarrayhead,
        myhlistid,
        myelementid1,
        2, // indentationstepsize,
        0); // currentindentationlevel);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error getting string stack depth, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (stringstackdepth != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got wrong string stack depth\n");
    }
    
    plstring = dg_getplstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID, 
        0, //  stringid,
        &lstringlength); // UINT64* pstringlength)
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - got an error getting pointer to lstring, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (lstringlength != 148)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - length not what was expected, expected 148, got ");
        dg_writestdoutuinttodec(&BHarrayhead, lstringlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        plstring, 
        lstringlength,
        (unsigned char*)"<root>myrootvalue\n  <element2>myelementvalue2\n    <element4>myelementvalue4</element4>\n  </element2>\n  <element3>myelementvalue3</element3>\n</root>\n",
        148,
		&compareflag);
        
    if (compareflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hlisttodglumlstring success case - result string not correct, expected:\n");
        dg_writestdout(
          &BHarrayhead, 
          (unsigned char*)"<root>myrootvalue\n  <element2>myelementvalue2\n    <element4>myelementvalue4</element4>\n  </element2>\n  <element3>myelementvalue3</element3>\n</root>\n",
          148);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"got:\n");
        dg_writestdout(&BHarrayhead, plstring, lstringlength);
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


// void (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))

void dg_testfunction1(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 parentelementid,
    unsigned char* pfunctionvalue,
    UINT64 functionvaluelength,
    Hlistheader* myhlistheader)
{
    dg_pushdatastack(pBHarrayhead, 1);
}

void dg_testfunction2(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 parentelementid,
    unsigned char* pfunctionvalue,
    UINT64 functionvaluelength,
    Hlistheader* myhlistheader)
{
    dg_pushdatastack(pBHarrayhead, 2);
}

void dg_testfunction3(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 parentelementid,
    unsigned char* pfunctionvalue,
    UINT64 functionvaluelength,
    Hlistheader* myhlistheader)
{
    UINT64 x = *((UINT64*)pfunctionvalue);
    
    dg_pushdatastack(pBHarrayhead, x);
}


unsigned char* dg_testfunctionnames = (unsigned char*)
    "func1func2func3";

UINT64 dg_linkfunctionnameoffsets[3] = {
    5,
    10,
    15};

UINT64 dg_linkfunctiontable[3] = {
    (UINT64)&dg_testfunction1,
    (UINT64)&dg_testfunction2,
    (UINT64)&dg_testfunction3};

UINT64 dg_linkfunctionsortedkeys[3] = {
    0,
    1,
    2};

void testdg_callhlistchildren()
{
    Bufferhandle BHarrayhead;
 
    UINT64 myhlistid;
    
    UINT64 myfakevalue = 99;
    
    UINT64 x;
    
    const char* pError;
    
    void (**pfunctions)(
        Bufferhandle*,
        UINT64,
        UINT64,
        unsigned char*,
        UINT64,
        Hlistheader*);
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_callhlistchildren\n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // need to make hlist containing names of functions to call
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"func1", // pname,
        5, // namelength,
        (unsigned char*)"myelementvalue", // pvalue,
        14); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got an error making new hlist element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"func2", // pname,
        5, // namelength,
        (unsigned char*)"myelementvalue", // pvalue,
        14); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got an error making new hlist element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"func3", // pname,
        5, // namelength,
        (unsigned char*)&myfakevalue, // pvalue,
        4); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got an error making new hlist element 3, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pfunctions = (void (**)(
            Bufferhandle*,
            UINT64,
            UINT64,
            unsigned char*,
            UINT64,
            Hlistheader*))&dg_linkfunctiontable;
    
    dg_callhlistchildren(
        &BHarrayhead,
        myhlistid,     // hlist containing function names to do
        0,             // parent element id in hlist containing function names to do
        24,            // function symbol list - actually. the list doesn't
        (unsigned char*)dg_linkfunctionsortedkeys,            //   change at run time so a key array is not necessary
        (UINT64*)dg_linkfunctionnameoffsets,
        dg_testfunctionnames,
        pfunctions);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got an error calling hlist children, got\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != myfakevalue)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got wrong value on top. Expected 99, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got wrong value 1 below top. Expected 2 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildren success case - got wrong value 1 below top. Expected 1 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    dg_clearerrors(&BHarrayhead);
   
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_packhlist()
{
    Bufferhandle BHarrayhead;
 
    UINT64 hlistid, elementid;
    UINT64 myunpackedhlistid;
    
    UINT64 packedhlistbufferid;
    

    
    unsigned char* pname;
    unsigned char* pvalue;
    UINT64 namelength;
    UINT64 valuelength;
    
    UINT64 indexofelementaftermatch;  // index in sort key lstring after match
    UINT64 foundelement;              // key = f[indexaftermatch - 1]
    
    UINT64 foundflag;
    
    const char* pError;
    INT64 myflag;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_packhlist\n");

    // empty hlist case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    hlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist success case - got an error making a new hlist, got\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    packedhlistbufferid = dg_packhlist(
        &BHarrayhead,
        hlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist success case - got an error making a new hlist, got\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myunpackedhlistid = dg_unpackhlist (
        &BHarrayhead,
        packedhlistbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist success case - got an error unpacking hlist, got\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // the unpacked hlist should be empty
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // hlist with stuff in it case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    hlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error making a new hlist, got\n");
        // // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    elementid = dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"Rootbeer", // pname,
        8, // namelength,
        (unsigned char*)"myrootvalue", // pvalue,
        11); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error making root element, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        elementid, // parentelementid,
        (unsigned char*)"carrot", // pname,
        6, // namelength,
        (unsigned char*)"bunny", // pvalue,
        5); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error making first child, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    elementid = dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        elementid, // parentelementid,
        (unsigned char*)"tomatoes", // pname,
        8, // namelength,
        (unsigned char*)"piz", // pvalue,
        3); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error making second child, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    elementid = dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        elementid, // parentelementid,
        (unsigned char*)"sub", // pname,
        3, // namelength,
        (unsigned char*)"ooga", // pvalue,
        4); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error making third child, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    packedhlistbufferid = dg_packhlist(
        &BHarrayhead,
        hlistid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error making a new hlist, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myunpackedhlistid = dg_unpackhlist (
        &BHarrayhead,
        packedhlistbufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error unpacking hlist, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_getshlistelement (
        &BHarrayhead,
        myunpackedhlistid,
        0, // root element
        &pname,
        &namelength,
        &pvalue,
        &valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error getting pointers to root element, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        pname,
        namelength,
        (unsigned char*)"Rootbeer",
        8,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - got an error comparing root names, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - root name wrong, expected 'Rootbeer', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pname);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_comparebytes (
        pvalue,
        valuelength,
        (unsigned char*)"myrootvalue",
        11,
		&myflag);
        
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case- got an error comparing root value, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (myflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - root value, expected 'myrootvalue', got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pvalue);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    foundflag = dg_findsortedhlistchild (
        &BHarrayhead,
        (unsigned char*)"carrot", // pname,
        6, // namelength,
        myunpackedhlistid,
        0, // root element
        &indexofelementaftermatch, // pindexofkeyaftermatch, // index in sort key lstring after match
        &foundelement); // key = f[indexaftermatch - 1]
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case- got an error finding child element of root, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (foundflag != 0) // 0 means equal
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_packhlist hlist with stuff in it case - did not find child element in root's sorted child list\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


const UINT64 my0 = 0;
const UINT64 my1 = 1;
const UINT64 my2 = 2;

void testdg_callhlistchildrenbyn() {
    Bufferhandle BHarrayhead;
 
    UINT64 myhlistid;
    
    UINT64 myfakevalue = 99;
    
    UINT64 x;
    
    const char* pError;
    
    void (**pfunctions)(
        Bufferhandle*,
        UINT64,
        UINT64,
        unsigned char*,
        UINT64,
        Hlistheader*);
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_callhlistchildrenbyn\n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    // need to make hlist containing names of functions to call
    myhlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got an error making new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)&my0, //"func1", // pname,
        sizeof(UINT64),    //5, // namelength,
        (unsigned char*)"myelementvalue", // pvalue,
        14); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got an error making new hlist element 1, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)&my1, // "func2", // pname,
        sizeof(UINT64),    //5, // namelength,
        (unsigned char*)"myelementvalue", // pvalue,
        14); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got an error making new hlist element 2, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        myhlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)&my2, //"func3", // pname,
        sizeof(UINT64),    //5, // namelength,
        (unsigned char*)&myfakevalue, // pvalue,
        4); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got an error making new hlist element 3, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pfunctions = (void (**)(
            Bufferhandle*,
            UINT64,
            UINT64,
            unsigned char*,
            UINT64,
            Hlistheader*))&dg_linkfunctiontable;
    
    dg_callhlistchildrenbyn(
        &BHarrayhead,
        myhlistid,         // hlist containing function names to do
        0, // parent element id in hlist containing function names to do
        3,
        pfunctions);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got an error calling hlist children, got\n");
        // dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != myfakevalue)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got wrong value on top. Expected 99, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got wrong value 1 below top. Expected 2 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_callhlistchildrenbyn success case - got wrong value 1 below top. Expected 1 got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    }
    
    dg_clearerrors(&BHarrayhead);
   
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_namestringtovaluestring()
{
    Bufferhandle BHarrayhead;

    UINT64 hlistid;    

    unsigned char* pvalue;

    UINT64 valuelength;
    
    INT64 myflag;
    
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_namestringtovaluestring\n");

    // empty hlist case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    hlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error making hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        (UINT64)-1, // parentelementid,
        (unsigned char*)"root", //"func3", // pname,
        4,    //5, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error making root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"name1", //"func3", // pname,
        5,    //5, // namelength,
        (unsigned char*)"value1", // pvalue,
        6); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error making 1st child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"namer2", //"func3", // pname,
        6,    //5, // namelength,
        (unsigned char*)"valuer2", // pvalue,
        7); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error making 2nd child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pvalue = dg_namestringtovaluestring(
        &BHarrayhead,
        hlistid,
        0,
        (unsigned char*)"name1",
        5,
        &valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error getting 1st value from 1st name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (valuelength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got wrong value length from 1st name expected 6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pError = dg_comparebytes (
        pvalue,
        valuelength,
        (unsigned char*)"value1",
        6,
		&myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error comparing value1 string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - value1 string did not match. Expected >>>value1<<<, got >>>");
        dg_writestdout(&BHarrayhead, pvalue, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    pvalue = dg_namestringtovaluestring(
        &BHarrayhead,
        hlistid,
        0,
        (unsigned char*)"namer2",
        6,
        &valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error getting 1st value from 2nd name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (valuelength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got wrong value length from 2nd name expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pError = dg_comparebytes (
        pvalue,
        valuelength,
        (unsigned char*)"valuer2",
        7,
		&myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - got an error comparing valuer2 string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestring success case - valuer2 string did not match. Expected >>>valuer2<<<, got >>>");
        dg_writestdout(&BHarrayhead, pvalue, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_namestringtovaluestringflag()
{
    Bufferhandle BHarrayhead;

    UINT64 hlistid;    

    unsigned char* pvalue;

    UINT64 valuelength;
    UINT64 wherefoundflag;
    
    INT64 myflag;
    
    const char* pError;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_namestringtovaluestringflag\n");

    // empty hlist case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    hlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error making hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        (UINT64)-1, // parentelementid,
        (unsigned char*)"root", //"func3", // pname,
        4,    //5, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error making root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"name1", //"func3", // pname,
        5,    //5, // namelength,
        (unsigned char*)"value1", // pvalue,
        6); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error making 1st child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_newhlistelement (
        &BHarrayhead,
        hlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"namer2", //"func3", // pname,
        6,    //5, // namelength,
        (unsigned char*)"valuer2", // pvalue,
        7); // valuelength);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error making 2nd child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pvalue = dg_namestringtovaluestringflag(
        &BHarrayhead,
        hlistid,
        0,
        (unsigned char*)"name1",
        5,
        &valuelength,
        &wherefoundflag);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error getting 1st value from 1st name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (valuelength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got wrong value length from 1st name expected 6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (wherefoundflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got wrong where found flag from 1st name expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, wherefoundflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pError = dg_comparebytes (
        pvalue,
        valuelength,
        (unsigned char*)"value1",
        6,
        &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error comparing value1 string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - value1 string did not match. Expected >>>value1<<<, got >>>");
        dg_writestdout(&BHarrayhead, pvalue, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    pvalue = dg_namestringtovaluestringflag(
        &BHarrayhead,
        hlistid,
        0,
        (unsigned char*)"namer2",
        6,
        &valuelength,
        &wherefoundflag);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error getting 1st value from 2nd name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (valuelength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got wrong value length from 2nd name expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (wherefoundflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got wrong wherefoundflag from 2nd name expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, wherefoundflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    pError = dg_comparebytes (
        pvalue,
        valuelength,
        (unsigned char*)"valuer2",
        7,
        &myflag);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error comparing valuer2 string, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (myflag != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - valuer2 string did not match. Expected >>>valuer2<<<, got >>>");
        dg_writestdout(&BHarrayhead, pvalue, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }

    pvalue = dg_namestringtovaluestringflag(
        &BHarrayhead,
        hlistid,
        0,
        (unsigned char*)"nameb",
        5,
        &valuelength,
        &wherefoundflag);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got an error getting 1st value from 3rd name, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (valuelength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got wrong value length from 3rd name expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (wherefoundflag == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - got wrong wherefoundflag from 3rd name expected not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, wherefoundflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
     
    if (pvalue != dg_emptystring)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_namestringtovaluestringflag success case - value not empty string, got >>>");
        dg_writestdout(&BHarrayhead, pvalue, valuelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"<<<\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

