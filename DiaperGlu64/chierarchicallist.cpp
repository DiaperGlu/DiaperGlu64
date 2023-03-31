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

const char* dg_sortedkeyslstringname = "dg_sortedkeyslstring";
 
// doing copies instead of just getting pointer because I don't want to have to 
  // worry about the buffer start addresses moving just yet.
const char* dg_gethlistheaderarrayheadername = "dg_gethlistheaderarrayheader";

void dg_gethlistheaderarrayheader(
    Bufferhandle* pBHarrayhead,
    Freeablelstringarrayheader* phlistheaderarrayheader,
    UINT64 hlistheaderarrayheaderlength)
{
    UINT64 hlistheaderarraybufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    hlistheaderarraybufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_hlistheaderbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistheaderarrayheadername);
        return;
    }
    
    if ((UINT64)dg_badbufferid == hlistheaderarraybufferid)
    {
        dg_pusherror(pBHarrayhead, dg_bufferidnotinbharray);
        dg_pusherror(pBHarrayhead, dg_forthhlistheaderarraybufferidname);
        dg_pusherror(pBHarrayhead, dg_gethlistheaderarrayheadername);
        return;
    }
    
    dg_getbuffersegment(
        pBHarrayhead, 
		hlistheaderarraybufferid, 
		0, 
		hlistheaderarrayheaderlength, 
		(unsigned char*)phlistheaderarrayheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistheaderarrayheadername);
        return;
    }
    
    // validate freeable lstring header magic - memory already validated by dg_getbuffersegment
    if (phlistheaderarrayheader->magic != dg_freeablelstringheadermagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_gethlistheaderarrayheadername);
        return;
    }
}


// doing copies instead of just getting pointer because I don't want to have to 
  // worry about the buffer start addresses moving just yet.
const char* dg_querycreatehlistheaderarrayname = "dg_querycreatehlistheaderarray";

UINT64 dg_querycreatehlistheaderarray(Bufferhandle* pBHarrayhead)
{
    UINT64 hlistheaderarraybufferid = (UINT64)dg_badbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(hlistheaderarraybufferid);
    }
    
    hlistheaderarraybufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_hlistheaderbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_querycreatehlistheaderarrayname);
        return(hlistheaderarraybufferid);
    }
    
    if ((UINT64)dg_badbufferid == hlistheaderarraybufferid)
    {
        // making new hlist header array
        hlistheaderarraybufferid = dg_newfreeablelstringarray(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            hlistheaderarraybufferid = (UINT64)dg_badbufferid;
            dg_pusherror(pBHarrayhead, dg_querycreatehlistheaderarrayname);
            return(hlistheaderarraybufferid);
        }
        
        dg_putbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_hlistheaderbuffer, hlistheaderarraybufferid);

        // this error can't really happen
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_querycreatehlistheaderarrayname);
            
            // this can't happed, but just in case freeing the freeable lstring array and not checking errors
            dg_freefreeablelstringarray(pBHarrayhead, hlistheaderarraybufferid);
            hlistheaderarraybufferid = (UINT64)dg_badbufferid;
            return(hlistheaderarraybufferid);
        }
    }
    
    return(hlistheaderarraybufferid);
}


const char* dg_gethlistheadername = "dg_gethlistheader";

void dg_gethlistheader(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    Hlistheader* phlistheader,
    UINT64 hlistheaderlength)
{
    struct Freeablelstringarrayheader myhlistheaderarrayheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_gethlistheaderarrayheader(
        pBHarrayhead,
        &myhlistheaderarrayheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistheadername);
        return;
    }
    
    dg_copysfromlstringn (
        pBHarrayhead,
		myhlistheaderarrayheader.lstringoffsetbufferid,
		myhlistheaderarrayheader.lstringstringbufferid,
		hlistheaderid,
        0,
        hlistheaderlength,
        (unsigned char*)phlistheader);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistheadername);
        return;
    }
    
    // if copy worked, then this memory access should work
    if (phlistheader->magic != dg_hlistheadermagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_gethlistheadername);
        return;
    }
}


const char* dg_freehlistmemoryname = "dg_freehlistmemory";

void dg_freehlistmemory (
    Bufferhandle* pBHarrayhead, 
    struct Hlistheader* phlist)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (phlist->elementheaderflstrbufid != (UINT64)dg_badbufferid)
    {
        dg_freefreeablelstringarray(
            pBHarrayhead, 
            phlist->elementheaderflstrbufid);
    }
   
    if (phlist->namelstroffsetbufid != (UINT64)dg_badbufferid)
    {
        dg_freebuffer(pBHarrayhead, phlist->namelstroffsetbufid);
    }
        
    if (phlist->namelstrstringbufid != (UINT64)dg_badbufferid)
    {
        dg_freebuffer(pBHarrayhead, phlist->namelstrstringbufid);
    }
        
    if (phlist->valuelstroffsetbufid != (UINT64)dg_badbufferid)
    {
        dg_freebuffer(pBHarrayhead, phlist->valuelstroffsetbufid);
    }
        
    if (phlist->valuelstrstringbufid != (UINT64)dg_badbufferid)
    {
        dg_freebuffer(pBHarrayhead, phlist->valuelstrstringbufid);
    }
        
    if (phlist->sortedchildidslstroffsetbufid != (UINT64)dg_badbufferid)
    {
        dg_freebuffer(pBHarrayhead, phlist->sortedchildidslstroffsetbufid);
    }
        
    if (phlist->sortedchildidslstrstringbufid != (UINT64)dg_badbufferid)
    {
        dg_freebuffer(pBHarrayhead, phlist->sortedchildidslstrstringbufid);
    }
    
    // only dg_freefreeablelstringarray can generate error at this time, 6/17/2011
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistmemoryname);
    }
}


// if I assume only dg_getnewhlist calls this function I could remove the memory protection checks
const char* dg_allocatehlistmemoryname = "dg_allocatehlistmemory";

void dg_allocatehlistmemory (
    Bufferhandle* pBHarrayhead, 
    struct Hlistheader* phlist, 
    UINT64 hlistlength)
{
    const char* pError;
    
    UINT64 n;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // if I can assume only dg_newhlist is the only routine calling this function, I could remove this check
    if (hlistlength < sizeof(Hlistheader))
    {
        dg_pusherror(pBHarrayhead, dg_allocatehlistmemoryname);
        return;
    }
    
    // allocating hlist elements header freeable lstring array
    n = dg_newfreeablelstringarray(pBHarrayhead);
    
    pError = dg_putuint64(&(phlist->elementheaderflstrbufid), n);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
    }
    
        if (olderrorcount == dg_geterrorcount(pBHarrayhead))
    {
        n = dg_newbuffer(
            pBHarrayhead,
			dg_defaultbuffergrowby,
			dg_defaultbuffermaxsize,
			&pError,
			FORTH_FALSE);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
        }
        
        pError = dg_putuint64(&(phlist->namelstroffsetbufid), n);
    
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
        }
    }
    
    if (olderrorcount == dg_geterrorcount(pBHarrayhead))
    {
        n = dg_newbuffer(
            pBHarrayhead,
			dg_defaultbuffergrowby,
			dg_defaultbuffermaxsize,
			&pError,
			FORTH_FALSE);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
        }
        
        pError = dg_putuint64(&(phlist->namelstrstringbufid), n);
    
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
        }
    }

    if (olderrorcount == dg_geterrorcount(pBHarrayhead))
    {
        n = dg_newbuffer(
            pBHarrayhead,
			dg_defaultbuffergrowby,
			dg_defaultbuffermaxsize,
			&pError,
			FORTH_FALSE);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
        }
        
        pError = dg_putuint64(&(phlist->valuelstroffsetbufid), n);
    
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
        }
    }

    if (olderrorcount == dg_geterrorcount(pBHarrayhead))
    {
        n = dg_newbuffer(
            pBHarrayhead,
			dg_defaultbuffergrowby,
			dg_defaultbuffermaxsize,
			&pError,
			FORTH_FALSE);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
        }
        
        pError = dg_putuint64(&(phlist->valuelstrstringbufid), n);
    
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
        }
    }

    if (olderrorcount == dg_geterrorcount(pBHarrayhead))
    {
        n = dg_newbuffer(
            pBHarrayhead,
			dg_defaultbuffergrowby,
			dg_defaultbuffermaxsize,
			&pError,
			FORTH_FALSE);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
        }
        
        pError = dg_putuint64(&(phlist->sortedchildidslstroffsetbufid), n);
    
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
        }
    }

    if (olderrorcount == dg_geterrorcount(pBHarrayhead))
    {
        n = dg_newbuffer(
            pBHarrayhead,
			dg_defaultbuffergrowby,
			dg_defaultbuffermaxsize,
			&pError,
			FORTH_FALSE);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
        }
        
        pError = dg_putuint64(&(phlist->sortedchildidslstrstringbufid), n);
    
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
        }
    }
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freehlistmemory (pBHarrayhead, phlist);
        dg_pusherror(pBHarrayhead, dg_allocatehlistmemoryname);
    }
}


const char* dg_newhlistname = "dg_newhlist";

UINT64 dg_newhlist (Bufferhandle* pBHarrayhead)
{
    UINT64 hlistheaderarraybufferid;
    
    struct Freeablelstringarrayheader myflstringarrayheader;
    UINT64 myhlistheaderarrayheaderlength = sizeof(Freeablelstringarrayheader);
    
    struct Hlistheader myhlist;
    
    UINT64 hlistheaderid = DG_ENDOFLIST;
    
    // initialize blank hlist header
    myhlist.magic = dg_hlistheadermagic;
    myhlist.elementheaderflstrbufid = (UINT64)dg_badbufferid;
    myhlist.namelstroffsetbufid = (UINT64)dg_badbufferid;
    myhlist.namelstrstringbufid = (UINT64)dg_badbufferid;
    myhlist.valuelstroffsetbufid = (UINT64)dg_badbufferid;
    myhlist.valuelstrstringbufid = (UINT64)dg_badbufferid;
    myhlist.sortedchildidslstroffsetbufid = (UINT64)dg_badbufferid;
    myhlist.sortedchildidslstrstringbufid = (UINT64)dg_badbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    // if hlistheaderarray does not exist, create it
    dg_querycreatehlistheaderarray(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistname);
        return (DG_ENDOFLIST);
    }
    
    dg_allocatehlistmemory(pBHarrayhead, &myhlist, sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistname);
        return (DG_ENDOFLIST);
    }
        
    // allocating slot in hlist header array
    hlistheaderarraybufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_hlistheaderbuffer);
        
    // can't really get this error
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freehlistmemory (pBHarrayhead, &myhlist);
        dg_pusherror(pBHarrayhead, dg_newhlistname);
        return (DG_ENDOFLIST);
    }
    
    hlistheaderid = dg_newfreeablelstring (
        pBHarrayhead,
        hlistheaderarraybufferid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freehlistmemory (pBHarrayhead, &myhlist);
            
        dg_pusherror(pBHarrayhead, dg_newhlistname);
        return (DG_ENDOFLIST);
    }
    
    // ok now put the new header into the new freeable lstring
    dg_gethlistheaderarrayheader(
        pBHarrayhead,
        &myflstringarrayheader,
        myhlistheaderarrayheaderlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freehlistmemory (pBHarrayhead, &myhlist);
        
        dg_freefreeablelstring(
            pBHarrayhead,
            hlistheaderarraybufferid,
            hlistheaderid);
            
        dg_pusherror(pBHarrayhead, dg_newhlistname);
        return (DG_ENDOFLIST);
    }
    
    dg_insertinlstring (
        pBHarrayhead,
        myflstringarrayheader.lstringoffsetbufferid,
        myflstringarrayheader.lstringstringbufferid,
        hlistheaderid,
        0,
        sizeof(Hlistheader));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freehlistmemory (pBHarrayhead, &myhlist);
        
        dg_freefreeablelstring(
            pBHarrayhead,
            hlistheaderarraybufferid,
            hlistheaderid);
            
        dg_pusherror(pBHarrayhead, dg_newhlistname);
        return (DG_ENDOFLIST);
    }
    
    dg_copystolstringn (
        pBHarrayhead,
        myflstringarrayheader.lstringoffsetbufferid,
        myflstringarrayheader.lstringstringbufferid,
        hlistheaderid,
        0,
        (unsigned char*)(&myhlist),
        sizeof(Hlistheader));

    // can't really get this error
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freehlistmemory (pBHarrayhead, &myhlist);
        
        dg_freefreeablelstring(
            pBHarrayhead,
            hlistheaderarraybufferid,
            hlistheaderid);
            
        dg_pusherror(pBHarrayhead, dg_newhlistname);
        return (DG_ENDOFLIST);
    }
    
    return (hlistheaderid);
}


const char* dg_freehlistname = "dg_freehlist";

void dg_freehlist (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid)
{
    Hlistheader myhlistheader;
    UINT64 hlistheaderarraybufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // hlist 0 is reserved for wordlists, not allowing user to free it directly to avoid accidents
    if (0 == hlistheaderid)
    {
        dg_pusherror(pBHarrayhead, dg_tryingtofreehlist0error);
        dg_pusherror(pBHarrayhead, dg_freehlistname);
        return;
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // couldn't get header so not gonna be able to do the rest of it, so might as well exit
        dg_pusherror(pBHarrayhead, dg_freehlistname);
        return;
    }
    
    // free the hlist's memory
    dg_freehlistmemory (pBHarrayhead, &myhlistheader);
    
    // ignoring errors because we still want to free the entry 
    //  - besides, since we already got header there won't be error freeing it
    hlistheaderarraybufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_hlistheaderbuffer);
    
    // free the hlist header
    dg_freefreeablelstring(
        pBHarrayhead,
        hlistheaderarraybufferid,
        hlistheaderid);
     
    // this error should not happen
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistname);
        return;
    }
}


const char* dg_linklasthlistchildelementname = "dg_linklasthlistchildelement";

void dg_linklasthlistchildelement (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementheaderid,
    UINT64 parentelementheaderid)
{
    Hlistheader myhlistheader;
    
    UINT64 lastchildelementheaderid = DG_ENDOFLIST;
    
    Hlistelementheader* pelementheader = (Hlistelementheader*)(badbufferhandle);
    Hlistelementheader* pparentelementheader = (Hlistelementheader*)(badbufferhandle);
    Hlistelementheader* plastchildelementheader = (Hlistelementheader*)(badbufferhandle);
    
    UINT64 elementheaderlength = 0;
    UINT64 parentelementheaderlength = 0;
    UINT64 lastchildelementheaderlength = 0;
    
    Freeablelstringarrayheader myelementheaderflstrah;
    
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    // get hlist element header freeable lstring header
   dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    // get pointer to element header
    pelementheader = (Hlistelementheader*)dg_getplstring(
        pBHarrayhead,
        myelementheaderflstrah.lstringoffsetbufferid,
        myelementheaderflstrah.lstringstringbufferid,
        elementheaderid,
        &elementheaderlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    if (elementheaderlength < sizeof(Hlistelementheader))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_getplstringname);
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    if (pelementheader->magic != dg_hlistelementmagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    pelementheader->parentelementid = parentelementheaderid;
    pelementheader->lastchildelementid = DG_ENDOFLIST;
    pelementheader->previoussiblingelementid = DG_ENDOFLIST;
    pelementheader->nextsiblingelementid = DG_ENDOFLIST;
    pelementheader->firstchildelementid = DG_ENDOFLIST;
    
    // get pointer to parent element header
    pparentelementheader = (Hlistelementheader*)dg_getplstring(
        pBHarrayhead,
        myelementheaderflstrah.lstringoffsetbufferid,
        myelementheaderflstrah.lstringstringbufferid,
        parentelementheaderid,
        &parentelementheaderlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // need error header missing
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    if (parentelementheaderlength < sizeof(Hlistelementheader))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_getplstringname);
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    if (pparentelementheader->magic != dg_hlistelementmagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
        return;
    }
    
    lastchildelementheaderid = pparentelementheader->lastchildelementid;
    pparentelementheader->lastchildelementid = elementheaderid;
    
    // get pointer to last child element header
    if (lastchildelementheaderid != DG_ENDOFLIST)
    {
        plastchildelementheader = (Hlistelementheader*)dg_getplstring(
            pBHarrayhead,
            myelementheaderflstrah.lstringoffsetbufferid,
            myelementheaderflstrah.lstringstringbufferid,
            lastchildelementheaderid,
            &lastchildelementheaderlength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            // need error header missing
            dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
            return;
        }
        
        if (lastchildelementheaderlength < sizeof(Hlistelementheader))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_getplstringname);
            dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
            return;
        }
    
        if (plastchildelementheader->magic != dg_hlistelementmagic)
        {
            dg_pusherror(pBHarrayhead, dg_badmagicerror);
            dg_pusherror(pBHarrayhead, dg_linklasthlistchildelementname);
            return;
        }
        
        plastchildelementheader->nextsiblingelementid = elementheaderid;
        pelementheader->previoussiblingelementid = lastchildelementheaderid;
    }
    else
    {
        pparentelementheader->firstchildelementid = elementheaderid;
    }
}


const char* dg_unlinkhlistchildelementname = "dg_unlinkhlistchildelement";

void dg_unlinkhlistchildelement (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementheaderid)
{
    Hlistheader myhlistheader;
    
    UINT64 previouschildelementheaderid = DG_ENDOFLIST;
    UINT64 nextchildelementheaderid = DG_ENDOFLIST;
    UINT64 parentelementheaderid = DG_ENDOFLIST;
    
    UINT64 lastchildelementheaderid = DG_ENDOFLIST;
    UINT64 firstchildelementheaderid = DG_ENDOFLIST;
    
    Hlistelementheader* pelementheader = (Hlistelementheader*)(badbufferhandle);
    Hlistelementheader* pparentelementheader = (Hlistelementheader*)(badbufferhandle);
    Hlistelementheader* ppreviouschildelementheader = (Hlistelementheader*)(badbufferhandle);
    Hlistelementheader* pnextchildelementheader = (Hlistelementheader*)(badbufferhandle);
    
    UINT64 elementheaderlength = 0;
    UINT64 parentelementheaderlength = 0;
    UINT64 nextchildelementheaderlength = 0;
    UINT64 previouschildelementheaderlength = 0;
    
    Freeablelstringarrayheader myelementheaderflstrah;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == elementheaderid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
        return;
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
        return;
    }
    
    // get hlist element header freeable lstring header
    dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
        return;
    }
    
    // get pointer to element header
    pelementheader = (Hlistelementheader*)dg_getplstring(
        pBHarrayhead,
        myelementheaderflstrah.lstringoffsetbufferid,
        myelementheaderflstrah.lstringstringbufferid,
        elementheaderid,
        &elementheaderlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
        return;
    }
    
    if (elementheaderlength < sizeof(Hlistelementheader))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_getplstringname);
        dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
        return;
    }
    
    if (pelementheader->magic != dg_hlistelementmagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
        return;
    }
    
    parentelementheaderid = pelementheader->parentelementid;
    nextchildelementheaderid = pelementheader->nextsiblingelementid;
    previouschildelementheaderid = pelementheader->previoussiblingelementid;
    
    // get pointer to parent element header
    if (parentelementheaderid != DG_ENDOFLIST)
    {
        pparentelementheader = (Hlistelementheader*)dg_getplstring(
            pBHarrayhead,
            myelementheaderflstrah.lstringoffsetbufferid,
            myelementheaderflstrah.lstringstringbufferid,
            parentelementheaderid,
            &parentelementheaderlength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            // need error header missing
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
    
        if (parentelementheaderlength < sizeof(Hlistelementheader))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_getplstringname);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        lastchildelementheaderid = pparentelementheader->lastchildelementid;
        firstchildelementheaderid = pparentelementheader->firstchildelementid;
    
        if (pparentelementheader->magic != dg_hlistelementmagic)
        {
            dg_pusherror(pBHarrayhead, dg_badmagicerror);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        // if last child is being deleted, make parent point to new last child
        if (elementheaderid == lastchildelementheaderid)
        {
            pparentelementheader->lastchildelementid = previouschildelementheaderid;
        }
        
        // if first child is being deleted, make parent point to new first child
        if (elementheaderid == firstchildelementheaderid)
        {
            pparentelementheader->firstchildelementid = nextchildelementheaderid;
        }
    }

    // get pointer to previous child element header
    if (previouschildelementheaderid != DG_ENDOFLIST)
    {
        ppreviouschildelementheader = (Hlistelementheader*)dg_getplstring(
            pBHarrayhead,
            myelementheaderflstrah.lstringoffsetbufferid,
            myelementheaderflstrah.lstringstringbufferid,
            previouschildelementheaderid,
            &previouschildelementheaderlength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            // need error header missing
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        // checking length of structure first before using pointer into structure
        if (previouschildelementheaderlength < sizeof(Hlistelementheader))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_getplstringname);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        if (ppreviouschildelementheader->magic != dg_hlistelementmagic)
        {
            dg_pusherror(pBHarrayhead, dg_badmagicerror);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        if (ppreviouschildelementheader->parentelementid != parentelementheaderid)
        {
            dg_pusherror(pBHarrayhead, dg_hlistpreviousparentbad);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        if (ppreviouschildelementheader->nextsiblingelementid != elementheaderid)
        {
            dg_pusherror(pBHarrayhead, dg_hlistpreviousnextbad);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        // link previous to next
        ppreviouschildelementheader->nextsiblingelementid = nextchildelementheaderid;
    }

    // get pointer to next child element header
    if (nextchildelementheaderid != DG_ENDOFLIST)
    {
        pnextchildelementheader = (Hlistelementheader*)dg_getplstring(
            pBHarrayhead,
            myelementheaderflstrah.lstringoffsetbufferid,
            myelementheaderflstrah.lstringstringbufferid,
            nextchildelementheaderid,
            &nextchildelementheaderlength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            // need error header missing
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        // checking length of structure first before using pointer into structure
        if (nextchildelementheaderlength < sizeof(Hlistelementheader))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_getplstringname);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        if (pnextchildelementheader->magic != dg_hlistelementmagic)
        {
            dg_pusherror(pBHarrayhead, dg_badmagicerror);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        if (pnextchildelementheader->parentelementid != parentelementheaderid)
        {
            dg_pusherror(pBHarrayhead, dg_hlistnextparentbad);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        if (pnextchildelementheader->previoussiblingelementid != elementheaderid)
        {
            dg_pusherror(pBHarrayhead, dg_hlistnextpreviousbad);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
            return;
        }
        
        // if there is a next, parent can not point to element
        if (elementheaderid == lastchildelementheaderid)
        {
            dg_pusherror(pBHarrayhead, dg_hlistparentlastchildbad);
            dg_pusherror(pBHarrayhead, dg_unlinkhlistchildelementname);
        }
        
        // link next to previous
        pnextchildelementheader->previoussiblingelementid = previouschildelementheaderid;
    }
}


const char* dg_newhlistelementname = "dg_newhlistelement";
        
UINT64 dg_newhlistelement (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
    unsigned char* pname,
    UINT64 namelength,
    unsigned char* pvalue,
    UINT64 valuelength)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    
    UINT64 elementid;
    
    UINT64 indexofkeyaftermatch, sortkey;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    myhlistelementheader.magic = dg_hlistelementmagic;
    myhlistelementheader.parentelementid = parentelementid;
    myhlistelementheader.lastchildelementid = DG_ENDOFLIST;
    myhlistelementheader.nextsiblingelementid = DG_ENDOFLIST;
    myhlistelementheader.previoussiblingelementid = DG_ENDOFLIST;
    //myhlistelementheader.key = 0; // key;
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // allocate lstrings for element
    // header freeable lstring array
    elementid = dg_newfreeablelstring (
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }

    // name lstring array
    dg_makesurelstringnexists (
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        elementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // value lstring array
    dg_makesurelstringnexists (
        pBHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        elementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // child sort keys lstring array
    dg_makesurelstringnexists (
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        elementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // insert header into element
    dg_insertsintoflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        elementid,
        0,
        (unsigned char*)&myhlistelementheader,
        sizeof(Hlistelementheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }

    // name
    dg_replacelstringn (
            pBHarrayhead,
			myhlistheader.namelstroffsetbufid,
			myhlistheader.namelstrstringbufid,
			elementid,
            pname,
            namelength);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // value
    dg_replacelstringn (
            pBHarrayhead,
			myhlistheader.valuelstroffsetbufid,
			myhlistheader.valuelstrstringbufid,
			elementid,
            pvalue,
            valuelength);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // child sort keys starts out empty                    
    // if parent element id is DG_ENDOFLIST it means this is a root element
    if (parentelementid != DG_ENDOFLIST)
    {
         // link element to end of parent's linked list of children
        dg_linklasthlistchildelement (
            pBHarrayhead,
            hlistid,
            elementid,
            parentelementid);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_newhlistelementname);
            return (DG_ENDOFLIST);
        }
        
        // with the addition of this routine I now have a circular test :-(
        dg_findsortedhlistchild (
            pBHarrayhead,
            pname,
            namelength,  
            hlistid, 
            parentelementid,      
            &indexofkeyaftermatch, // index in sort key lstring after match
            &sortkey);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_newhlistelementname);
            return (DG_ENDOFLIST);
        }
            
        dg_insertinlstring (
            pBHarrayhead,
            myhlistheader.sortedchildidslstroffsetbufid,
            myhlistheader.sortedchildidslstrstringbufid,
            parentelementid,
            indexofkeyaftermatch << 3, // in bytes - shouldn't need to check overflow since find routine won't return an index too big
            sizeof(UINT64));
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_newhlistelementname);
            return (DG_ENDOFLIST);
        }
            
        dg_copystolstringn (
            pBHarrayhead,
            myhlistheader.sortedchildidslstroffsetbufid,
            myhlistheader.sortedchildidslstrstringbufid,
            parentelementid,
            indexofkeyaftermatch << 3,
            (unsigned char*)(&elementid),
            sizeof(UINT64));
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_newhlistelementname);
            return (DG_ENDOFLIST);
        }
    }
    
    return (elementid);
}


// this will abandon any children of the element
const char* dg_freehlistelementname = "dg_freehlistelement";

void dg_freehlistelement (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementheaderid)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    Hlistelementheader myhlistparentelementheader;
    
    UINT64 myparentelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == elementheaderid)
    {
        // dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        // dg_pusherror(pBHarrayhead, dg_freehlistelementname);
        return;
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistelementname);
        return;
    }
    
    // copy element's header    
    dg_copysfromflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        elementheaderid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistelementheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistelementname);
        return;
    }
    
    myparentelementid = myhlistelementheader.parentelementid;
    
    // if parent element id is DG_ENDOFLIST it means this is a root element
    if (myparentelementid != DG_ENDOFLIST)
    {
        // copy parent's element header - need the parent's compare token    
        dg_copysfromflstrn(
            pBHarrayhead,
            myhlistheader.elementheaderflstrbufid,
            myhlistelementheader.parentelementid,
            0,
            sizeof(Hlistelementheader),
            (unsigned char*)&myhlistparentelementheader);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_freehlistelementname);
            return;
        }
    
        // unlink element from parent's linked list of children
        dg_unlinkhlistchildelement (
            pBHarrayhead,
            hlistheaderid,
            elementheaderid);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_freehlistelementname);
            return;
        }
        
        // remove element from parent's sorted list of child keys
          // could possibly speed this up by searching for the keys
          // with matching values first, then just scanning through
          // those for the key to remove
        dg_deleteuint64inlstringn (
            pBHarrayhead, 
            myhlistheader.sortedchildidslstroffsetbufid, // lstring holding sort key array
            myhlistheader.sortedchildidslstrstringbufid,
            myhlistelementheader.parentelementid, 
            elementheaderid);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_freehlistelementname);
            return;
        }
    }

    dg_setlengthlstringn (
        pBHarrayhead,
		myhlistheader.namelstroffsetbufid,
		myhlistheader.namelstrstringbufid,
		elementheaderid,
        0);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistelementname);
        return;
    }
    
    dg_setlengthlstringn (
        pBHarrayhead,
		myhlistheader.valuelstroffsetbufid,
		myhlistheader.valuelstrstringbufid,
		elementheaderid,
        0);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistelementname);
        return;
    }
    
    dg_setlengthlstringn (
        pBHarrayhead,
		myhlistheader.sortedchildidslstroffsetbufid,
		myhlistheader.sortedchildidslstrstringbufid,
		elementheaderid,
        0);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistelementname);
        return;
    }

    // free element header flstring
    dg_freefreeablelstring(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        elementheaderid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_freehlistelementname);
        return;
    }
    
    // if hlistheaderid is for wordlist
    if (0 == hlistheaderid)
    {
        // no errors from this routine
        dg_replaceerrors(
            pBHarrayhead,
            DG_WORDNAME_FAKE_BUFFERID,
            elementheaderid,
            DG_CORE_BUFFERID,
            (UINT64)dg_hlistelementwasfreed);
            
        // no errors from this routine
        dg_replaceerrors(
            pBHarrayhead,
            DG_WORDVALUE_FAKE_BUFFERID,
            elementheaderid,
            DG_CORE_BUFFERID,
            (UINT64)dg_hlistelementwasfreed);
    }        
}


const char* dg_gethlistlastchildofparentname = "dg_gethlistlastchildofparent";

UINT64 dg_gethlistlastchildofparent (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 parentelementid)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    if (DG_ENDOFLIST == parentelementid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_gethlistlastchildofparentname);
        return (DG_ENDOFLIST);
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistlastchildofparentname);
        return (DG_ENDOFLIST);
    }
    
    // copy element's header    
    dg_copysfromflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        parentelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistelementheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistlastchildofparentname);
        return (DG_ENDOFLIST);
    }
    
    return (myhlistelementheader.lastchildelementid);
}


const char* dg_gethlistfirstchildname = "dg_gethlistfirstchild";

UINT64 dg_gethlistfirstchild (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 parentelementid)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    if (DG_ENDOFLIST == parentelementid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_gethlistfirstchildname);
        return (DG_ENDOFLIST);
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistfirstchildname);
        return (DG_ENDOFLIST);
    }
    
    // copy element's header    
    dg_copysfromflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        parentelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistelementheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistfirstchildname);
        return (DG_ENDOFLIST);
    }
    
    return (myhlistelementheader.firstchildelementid);
}


// gets rid of all children but not the element itself
  // using recursion... be better to use non-recursive algorithm
const char* dg_prunehlistelementname = "dg_prunehlistelement";

void dg_prunehlistelement (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementheaderid)
{
    UINT64 latestchildelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    while (true)
    {
        latestchildelementid = dg_gethlistlastchildofparent (
            pBHarrayhead,
            hlistheaderid,
            elementheaderid); // parentelementid)
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_prunehlistelementname);
            return;
        }
            
        if (DG_ENDOFLIST == latestchildelementid)
        {
            break;
        }
        else
        {
            dg_prunehlistelement (
                pBHarrayhead,
                hlistheaderid,
                latestchildelementid);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_prunehlistelementname);
                return;
            }
            
            dg_freehlistelement (
                pBHarrayhead,
                hlistheaderid,
                latestchildelementid);
        
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_prunehlistelementname);
                return;
            }
        }
    }
}


const char* dg_gethlistnextsiblingname = "dg_gethlistnextsibling";

UINT64 dg_gethlistnextsibling (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 childelementid)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    if (DG_ENDOFLIST == childelementid)
    {
        return (DG_ENDOFLIST);
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistnextsiblingname);
        return (DG_ENDOFLIST);
    }
    
    // copy child element's header    
    dg_copysfromflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        childelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistelementheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistnextsiblingname);
        return (DG_ENDOFLIST);
    }
    
    return (myhlistelementheader.nextsiblingelementid);
}


const char* dg_gethlistprevioussiblingname = "dg_gethlistprevioussibling";

UINT64 dg_gethlistprevioussibling (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 childelementid)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    if (DG_ENDOFLIST == childelementid)
    {
        return (DG_ENDOFLIST);
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistprevioussiblingname);
        return (DG_ENDOFLIST);
    }
    
    // copy child element's header    
    dg_copysfromflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        childelementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistelementheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistprevioussiblingname);
        return (DG_ENDOFLIST);
    }
    
    return (myhlistelementheader.previoussiblingelementid);
}


const char* dg_gethlistelementparentname = "dg_gethlistelementparent";

UINT64 dg_gethlistelementparent (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementid)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    if (DG_ENDOFLIST == elementid)
    {
        return (DG_ENDOFLIST);
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistelementparentname);
        return (DG_ENDOFLIST);
    }
    
    // copy child element's header    
    dg_copysfromflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        elementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistelementheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gethlistelementparentname);
        return (DG_ENDOFLIST);
    }
    
    return (myhlistelementheader.parentelementid);
}


const char* dg_getshlistelementnomname = "dg_getshlistelementnom";

unsigned char* dg_getshlistelementnom (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementid,
    UINT64* pnamelength)
{
    Hlistheader myhlistheader;
    
    unsigned char* pname;
    
    UINT64 iselementfreeflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((unsigned char*)badbufferhandle);
    }
    
    if (DG_ENDOFLIST == elementid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_getshlistelementnomname);
        return ((unsigned char*)badbufferhandle);
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementnomname);
        return ((unsigned char*)badbufferhandle);
    }
    
    iselementfreeflag = dg_isfreeablelstringfree (
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid, // freeindexbuffer,
        elementid); // flstringid)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementnomname);
        return ((unsigned char*)badbufferhandle);
    }
    
    if (iselementfreeflag != FORTH_FALSE)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_getshlistelementnomname);
        return ((unsigned char*)badbufferhandle);
    }
    
    pname = dg_getplstring(
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        elementid,
        pnamelength); 
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementnomname);
        return ((unsigned char*)badbufferhandle);
    }
    
    return (pname);
}


const char* dg_getshlistelementvaluename = "dg_getshlistelementvalue";

unsigned char* dg_getshlistelementvalue (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementid,
    UINT64* pvaluelength)
{
    Hlistheader myhlistheader;
    
    unsigned char* pvalue;
    
    UINT64 iselementfreeflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((unsigned char*)badbufferhandle);
    }
    
    if (DG_ENDOFLIST == elementid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_getshlistelementvaluename);
        return ((unsigned char*)badbufferhandle);
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementvaluename);
        return ((unsigned char*)badbufferhandle);
    }
    
    iselementfreeflag = dg_isfreeablelstringfree (
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid, // freeindexbuffer,
        elementid); // flstringid)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementvaluename);
        return ((unsigned char*)badbufferhandle);
    }
    
    if (iselementfreeflag != FORTH_FALSE)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_getshlistelementvaluename);
        return ((unsigned char*)badbufferhandle);
    }
    
    pvalue = dg_getplstring(
        pBHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        elementid,
        pvaluelength); 
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementvaluename);
        return ((unsigned char*)badbufferhandle);
    }
    
    return (pvalue);
}


const char* dg_sethlistelementvaluename = "dg_sethlistelementvalue";

void dg_sethlistelementvalue (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementid,
    unsigned char* pvalue,
    UINT64 valuelength)
{
    Hlistheader myhlistheader;
    
    UINT64 iselementfreeflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == elementid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_sethlistelementvaluename);
        return;
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sethlistelementvaluename);
        return;
    }
    
    iselementfreeflag = dg_isfreeablelstringfree (
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid, // freeindexbuffer,
        elementid); // flstringid)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sethlistelementvaluename);
        return;
    }
    
    if (iselementfreeflag != FORTH_FALSE)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_sethlistelementvaluename);
        return;
    }
    
    dg_replacelstringn (
        pBHarrayhead,
		myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        elementid,
        pvalue,
        valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sethlistelementvaluename);
        return;
    }
}


const char* dg_getshlistelementname = "dg_getshlistelement";

void dg_getshlistelement (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementid,
    unsigned char** ppname,
    UINT64* pnamelength,
    unsigned char** ppvalue,
    UINT64* pvaluelength)
{
    Hlistheader myhlistheader;
    
    const char* pError;
    
    unsigned char* pname;
    unsigned char* pvalue;
    
    UINT64 iselementfreeflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == elementid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }
    
    iselementfreeflag = dg_isfreeablelstringfree (
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid, // freeindexbuffer,
        elementid); // flstringid)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }
    
    if (iselementfreeflag != FORTH_FALSE)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }

    // memory at pnamelength checked in getplstring function
    pname = dg_getplstring(
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        elementid,
        pnamelength); 
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }
    
    // memory at pvaluelength checked in getplstring function
    pvalue = dg_getplstring(
        pBHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        elementid,
        pvaluelength); 
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }

    pError = dg_putuint64((UINT64*)ppname, (UINT64)pname);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }
    
    pError = dg_putuint64((UINT64*)ppvalue, (UINT64)pvalue);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_getshlistelementname);
        return;
    }
}


const char* dg_sortcomparehlistnomname = "dg_sortcomparehlistnom";

INT64 dg_sortcomparehlistnom(
    Bufferhandle* pBHarrayhead,
    void* pcomparedata,
    UINT64 comparedatalength,
    UINT64 keyofmidrangevalue)
{
    // cast pcomparedata and custom compare data for this compare
    struct CompareNameData* pdata = (CompareNameData*)pcomparedata;
    INT64 compareresultflag = 1;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (compareresultflag);
    }
    
    // check pcomparedata
    if (comparedatalength != sizeof(CompareNameData))
    {
        dg_pusherror(pBHarrayhead, dg_sortcomparehlistnomname);
        return (compareresultflag);
    }
    
    compareresultflag = dg_comparestolstringn (
            pBHarrayhead,
            pdata->pname,
            pdata->namelength,
            pdata->namelstroffsetbufid, 
            pdata->namelstrstringbufid,
            keyofmidrangevalue);
                
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortcomparehlistnomname);
        return ((INT64)(-2));
    }
                
    return (compareresultflag);
}


const char* dg_dobinaryinsertsortstepname = "dg_dobinaryinsertsortstep";

UINT64 dg_dobinaryinsertsortstep (
    Bufferhandle* pBHarrayhead,
    unsigned char* psortedkeyslstring,
    UINT64 sortedkeyslength,
    INT64 (*pcompareroutine)(Bufferhandle*, void*, UINT64, UINT64),
    void* pcomparedata,
    UINT64 comparedatalength,
    UINT64* pstartindex,
    UINT64* pendindex,
    UINT64* ptofindbeforerangeflag,
    UINT64* ploopdoneflag)
{
//    UINT64 foundflag = FORTH_FALSE;
    UINT64 rangetocheck;
    UINT64 keyofmidrangevalue;
    INT64 compareresultflag = -2;
    UINT64 startindexinsortedkeyarray;
    UINT64 endindexinsortedkeyarray;
    UINT64 midrangeindexinsortedkeyarray;
    UINT64 tofindtobeforerangeflag;
    
    
    struct CompareNameData* pdata = (CompareNameData*)pcomparedata;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)(-2));
    }
    
    // going to make assumptions about validity of input parameters for speed purposes
    startindexinsortedkeyarray = *pstartindex;
    
    endindexinsortedkeyarray = *pendindex;
    
    tofindtobeforerangeflag = *ptofindbeforerangeflag;
    
    *ploopdoneflag = FORTH_TRUE;
    
    rangetocheck = endindexinsortedkeyarray - startindexinsortedkeyarray;
         
    // empty list case which can only happen first time through loop
    if (0 == rangetocheck)
    {
        // case 0 - empty list case
        //  unless algorithm is broken, list is empty so
        //  return index 0 and say input item is greater than all before it in list
        //  so that an insert will happen 'before' index 0
            
        // tofindtobeforerangeflag = 1; // tofindtobeforerangeflag is already 1
        // *pindexofkeyaftermatch = 0; // startindexinsortedkeyarray is already 0
        *ploopdoneflag = FORTH_TRUE;
        return ((UINT64)(-2));
    }
        
    if (1 == rangetocheck)
    {
        //keyofmidrangevalue = dg_getbufferuint64(pBHarrayhead, sortedkeysbufferid, startindexinsortedkeyarray << 3);
        keyofmidrangevalue = ((UINT64*)psortedkeyslstring)[startindexinsortedkeyarray];
        
        *ploopdoneflag = FORTH_TRUE;
            
        //compareresultflag = (*pcompareroutine) (
        //    pBHarrayhead, 
        //    pcomparedata,
        //    comparedatalength,
        //    keyofmidrangevalue);
            
        compareresultflag = dg_comparestolstringn (
            pBHarrayhead,
            pdata->pname,
            pdata->namelength,
            pdata->namelstroffsetbufid, 
            pdata->namelstrstringbufid,
            keyofmidrangevalue);
                
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_dobinaryinsertsortstepname);
            return ((UINT64)(-2));
        }
            
        if (((INT64)(largestunsignedint)) == compareresultflag) // if less than
        {
            endindexinsortedkeyarray--; // not necessary since start index is used, but for test simplicity
                // break;
        }
        else // if greater than or equal
        {
            startindexinsortedkeyarray++;
            tofindtobeforerangeflag = compareresultflag;
            // break;
        }
    }
        
    else if (2 == rangetocheck)
    {
            // case 2 - 2 items in list
            //  everything after remaining items is greater than, everything before is less than or equal
            //  check halfway item (item 1 of 0,1 for only 2 items)
            //  if equal, return 'equal' and index after item so insert will go after this item
            //  if new item < halfway item then everything from halfway item and before is before and everything after is already after so
            //   return 'greater than' and index after item so insert will go after this item
            //  if new item > halfway item then need to check item before it for equal so
            //   do case 1 on next pass for item 0 from this pass

            // do compare
            //keyofmidrangevalue = dg_getbufferuint64(pBHarrayhead, sortedkeysbufferid, (startindexinsortedkeyarray + 1) << 3);
        keyofmidrangevalue = ((UINT64*)psortedkeyslstring)[startindexinsortedkeyarray + 1];
            
        //compareresultflag = (*pcompareroutine) (
        //    pBHarrayhead, 
        //    pcomparedata,
        //    comparedatalength,
        //    keyofmidrangevalue);
            
        compareresultflag = dg_comparestolstringn (
            pBHarrayhead,
            pdata->pname,
            pdata->namelength,
            pdata->namelstroffsetbufid, 
            pdata->namelstrstringbufid,
            keyofmidrangevalue);
                
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            *ploopdoneflag = FORTH_TRUE;
            dg_pusherror(pBHarrayhead, dg_dobinaryinsertsortstepname);
            return (compareresultflag);
        }
            
        if (((INT64)(largestunsignedint)) == compareresultflag)  // less than
        {
            // need to check first element - throwing away last element
            endindexinsortedkeyarray--;
            *ploopdoneflag = FORTH_FALSE;
        }
        else // greater than or equal
        {
            // new element goes after last element in range
            tofindtobeforerangeflag = compareresultflag;
            startindexinsortedkeyarray = endindexinsortedkeyarray;
            *ploopdoneflag = FORTH_TRUE; //break;
        }
    }
    else  // 3 or more items left case
    {
            // case 3 - 3 or more items in list
            //  everything after remaining items is greater than, everything before is less than or equal
            //  check halfway item rounding down
            //  if new item less than or equal halfway item, then everything before and including item is less than or equal, 
            //   but you do not know if any of the items after the half way item are equal too so need to check them
            //  if new item greater than halfway item then everything after and including halfway item is greater than, but you do know know about 
            //   before the halfway item even if it is only 1 item for the 3 item left case, you still need to check it for = so
            //   on next pass check remaining area before item, you do not need to recheck the item
        
            // variables are bounded by this routine so no need to check for overflow
        midrangeindexinsortedkeyarray = startindexinsortedkeyarray + (rangetocheck >> 1);
            
        // do compare
        //keyofmidrangevalue = dg_getbufferuint64(pBHarrayhead, sortedkeysbufferid, midrangeindexinsortedkeyarray << 3);
        keyofmidrangevalue = ((UINT64*)psortedkeyslstring)[midrangeindexinsortedkeyarray];
            
        //compareresultflag = (*pcompareroutine) (
        //    pBHarrayhead, 
        //    pcomparedata,
        //    comparedatalength,
        //    keyofmidrangevalue);
            
        compareresultflag = dg_comparestolstringn (
            pBHarrayhead,
            pdata->pname,
            pdata->namelength,
            pdata->namelstroffsetbufid, 
            pdata->namelstrstringbufid,
            keyofmidrangevalue);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            *ploopdoneflag = FORTH_TRUE; //break;
            dg_pusherror(pBHarrayhead, dg_dobinaryinsertsortstepname);
            return ((UINT64)(-2));
        }
            
        if (((INT64)(largestunsignedint)) == compareresultflag) // if less than 
        {
            *ploopdoneflag = FORTH_FALSE;
            endindexinsortedkeyarray = midrangeindexinsortedkeyarray;
        }
        else // else greater than or equal
        {
            *ploopdoneflag = FORTH_FALSE;
            tofindtobeforerangeflag = compareresultflag;
            startindexinsortedkeyarray = midrangeindexinsortedkeyarray+1; // check items after halfway item
        }
    }
    
    *ptofindbeforerangeflag = tofindtobeforerangeflag;
    *pstartindex = startindexinsortedkeyarray;
    *pendindex = endindexinsortedkeyarray;

    // just to make visual studio happy, subroutine doesn't actually return from here
    return (compareresultflag);
}


const char* dg_findsortedhlistchildsubname = "dg_findsortedhlistchildsub";

UINT64 dg_findsortedhlistchildsub (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength,
    UINT64 sortedkeyslstringlength,
    unsigned char* psortedkeyslstring,
    // UINT64* pnamelstringoffsetbufferlength,
    UINT64* pnamelstringoffsetbuffer,
    // UINT64* pnamelstringstringbufferlength,
    unsigned char* pnamelstringstringbuffer,
    UINT64* pindexofkeyaftermatch, // index in sort key lstring after match
    UINT64* pkey)
{
    UINT64 namelstringlength;
    unsigned char* pnamelstring;
    
    UINT64 tofindtobeforerangeflag = 1; // at start item to find is greater than imaginary item before range
    
    UINT64 startindexinsortedkeyarray = 0;
    UINT64 midrangeindexinsortedkeyarray = 0;
    UINT64 rangetocheck = 0;
    UINT64 keyofmidrangevalue = 0;
    
    UINT64 compareresultflag = ((UINT64)(-2));
    
    const char* pError;
    
    UINT64 loopdoneflag = FORTH_FALSE;
    
    UINT64 endindexinsortedkeyarray = sortedkeyslstringlength >> 3; // /sizeof(UINT64)
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)(-2)); // probably should return a bad find index
    }
            
    while (FORTH_FALSE == loopdoneflag)
    {
        // going to make assumptions about validity of input parameters for speed purposes
        loopdoneflag = FORTH_TRUE;
    
        rangetocheck = endindexinsortedkeyarray - startindexinsortedkeyarray;
        
        // variables are bounded by this routine so no need to check for overflow
        midrangeindexinsortedkeyarray = startindexinsortedkeyarray + (rangetocheck >> 1);
            
        //keyofmidrangevalue = dg_getbufferuint64(pBHarrayhead, sortedkeysbufferid, midrangeindexinsortedkeyarray << 3);
        keyofmidrangevalue = ((UINT64*)psortedkeyslstring)[midrangeindexinsortedkeyarray];
        
        // empty list case which can only happen first time through loop
        if (0 == rangetocheck)
        {
            // case 0 - empty list case
            //  unless algorithm is broken, list is empty so
            //  return index 0 and say input item is greater than all before it in list
            //  so that an insert will happen 'before' index 0
            
            //loopdoneflag = FORTH_TRUE;
            return ((UINT64)(-2));
        }
        
        // assuming lstring name array is ok... not doing safety checks for speed
        if (0 == keyofmidrangevalue)
        {
            namelstringlength = pnamelstringoffsetbuffer[0];
            pnamelstring = pnamelstringstringbuffer;
        }
        else
        {
            namelstringlength =
                pnamelstringoffsetbuffer[keyofmidrangevalue] -
                pnamelstringoffsetbuffer[keyofmidrangevalue - 1];
                
            pnamelstring = pnamelstringstringbuffer + pnamelstringoffsetbuffer[keyofmidrangevalue - 1];
        }
        
        /*
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nfind - comparing word >>>");
        dg_writestdout(
            pBHarrayhead,
            pnamelstring,
            namelstringlength);
         dg_printzerostring(pBHarrayhead, (unsigned char*)"<<<\n");
        */
        
        // if I turn off memory protection... it will be even faster...
        pError = dg_comparebytes(
            pname,
            namelength,
            pnamelstring,
            namelstringlength,
            (INT64*)&compareresultflag);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, dg_comparebytesname);
            dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
            return ((UINT64)(-2));
        }

        if (((UINT64)(largestunsignedint)) == compareresultflag) // if less than 
        {
            if (rangetocheck < 2)
            {
                loopdoneflag = FORTH_TRUE;
            }
            else
            {
                loopdoneflag = FORTH_FALSE;
            }
            
            endindexinsortedkeyarray = midrangeindexinsortedkeyarray;
        }
        else // else greater than or equal
        {
            if (rangetocheck < 3)
            {
                loopdoneflag = FORTH_TRUE;
            }
            else
            {
                loopdoneflag = FORTH_FALSE;
            }
            
            tofindtobeforerangeflag = compareresultflag;
            startindexinsortedkeyarray = midrangeindexinsortedkeyarray+1; // check items after halfway item
        }
    }
    
    // I think with what I have above I won't need to search ahead for first non-match
    //   since I'm only cutting off on less than or greater equal
    
    *pindexofkeyaftermatch = startindexinsortedkeyarray;
    
    if (startindexinsortedkeyarray != 0)
    {
        *pkey = ((UINT64*)psortedkeyslstring)[(startindexinsortedkeyarray-1)];
    }
    
    return (tofindtobeforerangeflag);
}

// when loading dylibs, many words are usually in order already
//  so I could probably speed this up by keeping track of if the 
//  last word added was the highest word in the list, then when adding
//  the next word, we can start by checking against the previous last word
//  hmm is this what mac os x does with it's dylib search hint feature?

// to do this, on first pass if there are 3 or more elements, probably can use last element as mid range value

// this routine finds an hlist child sorted by name
const char* dg_findsortedhlistchildname = "dg_findsortedhlistchild";
//const char* dg_sortedkeyslstringname = "sorted keys lstring";

UINT64 dg_findsortedhlistchild (
  Bufferhandle* pBHarrayhead,
  unsigned char* pname,
  UINT64 namelength,
  UINT64 hlistheaderid, 
  UINT64 parentelementid,      
  UINT64* pindexofkeyaftermatch, // index in sort key lstring after match
  UINT64* pkey) // key = f[indexaftermatch - 1]
  
  // this routine searches an array of sorted keys stored in an lstring for the first name whose value is greater than
  //  than the name you are trying to find
  // sort key array index of element id after match is returned so you can do a normal diaperglu before item insert
  // return value is a standard forth compare flag
  //   0 means f(sortkeyindexaftermatch -1) is same, 
  //   1 means f(sortkeyindexaftermatch -1) is greater than or you had an empty list
  //   -1 can't happen but would mean f(indexaftermatch -1) was less than
  //   anything other than 0 or 1 is an error, gonna use -2 for error
  // so at start of find, the entire sort key array range is included and the item you are looking for is automatically
  //  assumed to be greater than the imaginary item before the start of the list
  //  when comparing, if item you are looking for is less than the item in the sort key array, then you can throw away
  //   the item in the sort key array and everything after it, and just search everything before the item
  //   in this case the item before the range you are searching doesn't change so if it was equal
  //   it stays equal. If it was less than, it stays less than.
  //  if the item you are looking for is equal to the item in the sortkeyarray then
  //   you can throw away the item and everything before it. In this case the item before the range
  //   becomes equal
  //  if the item you are looking for is greater than the item in the sortkeyarray then
  //   you can throw away the item and everything before it. In this case the item before the range
  //   becomes less than.
{
    Hlistheader myhlistheader;
    Freeablelstringarrayheader myelementheaderflstrah;
    
    UINT64 tofindtobeforerangeflag = 1; // at start item to find is greater than imaginary item before range
    
    UINT64 sortedkeyslstringlength = 0;
    unsigned char* psortedkeyslstring;
    
    UINT64* pnamelstringoffsetbufferlength;
    UINT64* pnamelstringoffsetbuffer;
    
    UINT64* pnamelstringstringbufferlength;
    unsigned char* pnamelstringstringbuffer;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)(-2)); // probably should return a bad find index
    }
    
    if (DG_ENDOFLIST == parentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return (DG_ENDOFLIST);
    }
    
    //*pindexofkeyaftermatch = 0;
    pError = dg_putuint64(pindexofkeyaftermatch, 0);
    
    // check for bad memory at pindexofkeyaftermatch
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return((UINT64)(-2));
    }
    
    //*pkey = DG_ENDOFLIST;
    pError = dg_putuint64(pkey, DG_ENDOFLIST);
    
    // check for bad memory at pkey, this is the found key
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return((UINT64)(-2));
    }
    
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return ((UINT64)(-2));
    }
    
    // get hlist element header freeable lstring header
   dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return ((UINT64)(-2));
    }
    
    psortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        parentelementid,
        &sortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return ((UINT64)(-2));
    }
    
    if ((sortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return ((UINT64)(-2));
    }
    
    
    pnamelstringoffsetbuffer = (UINT64*)dg_getpbuffer (
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid,
        &pnamelstringoffsetbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return ((UINT64)(-2));
    }
    
    
    pnamelstringstringbuffer = dg_getpbuffer (
        pBHarrayhead,
        myhlistheader.namelstrstringbufid,
        &pnamelstringstringbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return ((UINT64)(-2));
    }
    
    tofindtobeforerangeflag = dg_findsortedhlistchildsub (
        pBHarrayhead,
        pname,
        namelength,
        sortedkeyslstringlength,
        psortedkeyslstring,
        // pnamelstringoffsetbufferlength,
        pnamelstringoffsetbuffer,
        // pnamelstringstringbufferlength,
        pnamelstringstringbuffer,
        pindexofkeyaftermatch, // index in sort key lstring after match
        pkey);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_findsortedhlistchildname);
        return ((UINT64)(-2));
    }
    
    return (tofindtobeforerangeflag);
}


// this is for error stack routine use
const char* dg_getshlistelementnamenename = "dg_getshlistelementnamene";

const char* dg_getshlistelementnamene (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 elementid,
    unsigned char** ppname,
    UINT64* pnamelength)
{
    const char* pError;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (dg_errorinsubroutine); // just need something other than dg_success
    }
    
    pError = dg_putuint64((UINT64*)ppname, (UINT64)badbufferhandle);
    
    if (dg_success != pError)
    {
        return(pError);
    }
    
    *ppname = dg_getshlistelementnom (
        pBHarrayhead,
        hlistheaderid,
        elementid,
        pnamelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_droptoerrorcount (pBHarrayhead, olderrorcount);
        return(dg_errorinsubroutine);
    }
    
    return (dg_success);
}

// need add element index to sort key array using the tag/name/key find
// need to modify new hlist element to use new add element
// need to modify free hlist element maybe... don't think so...

const char* dg_changehlistelementparentname = "dg_changehlistelementparent";

void dg_changehlistelementparent (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    UINT64 newparentelementid)
{
    Hlistheader myhlistheader;
    Hlistelementheader myhlistelementheader;
    
    Freeablelstringarrayheader myelementheaderflstrah;
    
    Hlistelementheader* pelementheader;
    UINT64 elementheaderlength;
    
    UINT64 oldparentelementid;
    
    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 indexofkeyaftermatch;
    UINT64 sortkey;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == elementid)
    {
        dg_pusherror(pBHarrayhead, dg_elementisfreeerror);
        dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
        return;
    }
    
    // get the hlist header 
    dg_gethlistheader(
        pBHarrayhead,
        hlistid,
        &myhlistheader,
        sizeof(Hlistheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
        return;
    }
    
    // copy element's header    
    dg_copysfromflstrn(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        elementid,
        0,
        sizeof(Hlistelementheader),
        (unsigned char*)&myhlistelementheader);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
        return;
    }
    
    oldparentelementid = myhlistelementheader.parentelementid;
    
    // if parent element id is DG_ENDOFLIST it means this is a root element
    if (oldparentelementid != DG_ENDOFLIST)
    {
        // unlink element from parent's linked list of children
        dg_unlinkhlistchildelement (
            pBHarrayhead,
            hlistid,
            elementid);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
            return;
        }
        
        // remove element from parent's sorted list of child keys
          // could possibly speed this up by searching for the keys
          // with matching values first, then just scanning through
          // those for the key to remove
        dg_deleteuint64inlstringn (
            pBHarrayhead, 
            myhlistheader.sortedchildidslstroffsetbufid, // lstring holding sort key array
            myhlistheader.sortedchildidslstrstringbufid,
            oldparentelementid, 
            elementid);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
            return;
        }
    }
    
    // child sort keys starts out empty                    
    // if parent element id is DG_ENDOFLIST it means this is a root element
    if (newparentelementid != DG_ENDOFLIST)
    {
        dg_getshlistelement (
            pBHarrayhead,
            hlistid,
            elementid,
            &pname,
            &namelength,
            &pvalue,
            &valuelength);
    
         // link element to end of parent's linked list of children
        dg_linklasthlistchildelement (
            pBHarrayhead,
            hlistid,
            elementid,
            newparentelementid);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
            return;
        }
        
        // with the addition of this routine I now have a circular test :-(
        dg_findsortedhlistchild (
            pBHarrayhead,
            pname,
            namelength,
            hlistid, 
            newparentelementid,      
            &indexofkeyaftermatch, // index in sort key lstring after match
            &sortkey);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
            return;
        }
            
        dg_insertinlstring (
            pBHarrayhead,
            myhlistheader.sortedchildidslstroffsetbufid,
            myhlistheader.sortedchildidslstrstringbufid,
            newparentelementid,
            indexofkeyaftermatch << 3, // in bytes - shouldn't need to check overflow since find routine won't return an index too big
            sizeof(UINT64));
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
            return;
        }
            
        dg_copystolstringn (
            pBHarrayhead,
            myhlistheader.sortedchildidslstroffsetbufid,
            myhlistheader.sortedchildidslstrstringbufid,
            newparentelementid,
            indexofkeyaftermatch << 3,
            (unsigned char*)(&elementid),
            sizeof(UINT64));
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
            return;
        }
    }
    
    // now actually change the element's parent
    // get hlist element header freeable lstring header
    dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
        return;
    }
    
    // get pointer to element header
    pelementheader = (Hlistelementheader*)dg_getplstring(
        pBHarrayhead,
        myelementheaderflstrah.lstringoffsetbufferid,
        myelementheaderflstrah.lstringstringbufferid,
        elementid,
        &elementheaderlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
        return;
    }
    
    if (elementheaderlength < sizeof(Hlistelementheader))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_getplstringname);
        dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
        return;
    }
    
    if (pelementheader->magic != dg_hlistelementmagic)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_changehlistelementparentname);
        return;
    }
    
    pelementheader->parentelementid = newparentelementid;
}
    
const char* dg_getnumberofsortedchildrenname = "dg_getnumberofsortedchildren";

UINT64 dg_getnumberofsortedchildren(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 parentelementid)
{
    Hlistheader myhlistheader;
    Freeablelstringarrayheader myelementheaderflstrah;
    
    UINT64 sortedkeyslstringlength = 0;
    unsigned char* psortedkeyslstring;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)(-2)); // probably should return a bad find index
    }
    
    if (DG_ENDOFLIST == parentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return (DG_ENDOFLIST);
    }
    
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getnumberofsortedchildrenname);
        return ((UINT64)(-2));
    }
    
    // get hlist element header freeable lstring header
   dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getnumberofsortedchildrenname);
        return ((UINT64)(-2));
    }
    
    psortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        parentelementid,
        &sortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_getnumberofsortedchildrenname);
        return ((UINT64)(-2));
    }
    
    if ((sortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_getnumberofsortedchildrenname);
        return ((UINT64)(-2));
    }
    
    return (sortedkeyslstringlength >> 3); // /sizeof(UINT64)
}


const char* dg_getidofsortedhlistchildnname = "dg_getidofsortedhlistchildnid";

UINT64 dg_getidofsortedhlistchildn(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 parentelementid,
    UINT64 sortkeyindex)
{
    Hlistheader myhlistheader;
    Freeablelstringarrayheader myelementheaderflstrah;
    
    UINT64 sortedkeyslstringlength = 0;
    unsigned char* psortedkeyslstring;
    
    UINT64 numberofsortedchildren;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST); // probably should return a bad find index
    }
    
    if (DG_ENDOFLIST == parentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return (DG_ENDOFLIST);
    }
    
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getidofsortedhlistchildnname);
        return (DG_ENDOFLIST);
    }
    
    // get hlist element header freeable lstring header
   dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getidofsortedhlistchildnname);
        return (DG_ENDOFLIST);
    }
    
    psortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        parentelementid,
        &sortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_getidofsortedhlistchildnname);
        return (DG_ENDOFLIST);
    }
    
    if ((sortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_getidofsortedhlistchildnname);
        return (DG_ENDOFLIST);
    }
    
    numberofsortedchildren = sortedkeyslstringlength >> 3;
    
    if (sortkeyindex > numberofsortedchildren)
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_getidofsortedhlistchildnname);
        return (DG_ENDOFLIST);
    }
    
    return (((UINT64*)psortedkeyslstring)[sortkeyindex]);
}


const char* dg_addnsamechartostringname = "dg_addnsamechartostring";

void dg_addnsamechartostring (
    Bufferhandle* pBHarrayhead,
    UINT64 n,
    unsigned char c)
{
    UINT64 stringstackdepth;
    UINT64 topstringlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (0 == n)
    {
        return;
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_addnsamechartostringname);
		return;
	}
    
    if (0 == stringstackdepth)
    {
        return;
    }
    
    topstringlength = dg_getlstringlength(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        stringstackdepth - 1);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_addnsamechartostringname);
		return;
	}
    
    dg_insertwithcfillinlstringn (
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        topstringlength, // offset,
        n, // length,
        c); // cvalue)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_addnsamechartostringname);
		return;
	}
}


const char* dg_hlisttodglumlstringname = "dg_hlisttodglumlstring";

void dg_hlisttodglumlstring (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 rootelementid,
    UINT64 indentationstepsize,
    UINT64 currentindentationlevel)
{
    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 i, x;
    
    UINT64 numberofsortedchildren;
    
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_getshlistelement (
        pBHarrayhead,
        hlistid,
        rootelementid,
        &pname,
        &namelength,
        &pvalue,
        &valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
    
    dg_addnsamechartostring (
        pBHarrayhead,
        currentindentationlevel,
        ' ');
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
    
    // <
    dg_stotoplstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        (unsigned char*)"<");
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
    
    // name
    // dg_forthnewstring(pBHarrayhead);
    dg_pushlstring(pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		0,
		(unsigned char*)"");
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
        
    dg_stotoplstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID,
        namelength,
        pname);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
        
    // dg_forthurlencodestring(pBHarrayhead);
    dg_urlencodelstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
        
    // dg_forthcatstring(pBHarrayhead);
    dg_catlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
    
    // >
    dg_stotoplstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
        1,
        (unsigned char*)">");
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
    
    if (valuelength != 0)
    {
        // dg_forthnewstring(pBHarrayhead);
        dg_pushlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            0,
            (unsigned char*)"");
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
            return;
        }
        
        // value
        dg_stotoplstring (
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID, 
            DG_STRINGSTRINGSTACK_BUFFERID,
            valuelength,
            pvalue);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
            return;
        }
        
        // dg_forthurlencodestring(pBHarrayhead);
        dg_urlencodelstring (
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
            return;
        }
        
        // dg_forthcatstring(pBHarrayhead);
        dg_catlstring (
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
            return;
        }
   }
    
    // get s sorted children
    // recursively call this routine indented
    numberofsortedchildren = dg_getnumberofsortedchildren(
        pBHarrayhead,
        hlistid,
        rootelementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }

        
    if (numberofsortedchildren != 0)
    {
        // CR
        dg_stotoplstring (
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID, 
            DG_STRINGSTRINGSTACK_BUFFERID,
            1,
            (unsigned char*)"\n");
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
            return;
        }

        for (i = 0; i < numberofsortedchildren; i++)
        {
            x = dg_getidofsortedhlistchildn(
                pBHarrayhead,
                hlistid,
                rootelementid,
                i);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
                return;
            }
            
            dg_hlisttodglumlstring (
                pBHarrayhead,
                hlistid,
                x,
                indentationstepsize,
                currentindentationlevel + indentationstepsize);
            
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
                return;
            }
        }
        
        dg_addnsamechartostring (
            pBHarrayhead,
            currentindentationlevel,
            ' ');
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
            return;
        }
    }
    
    // </name>
    dg_stotoplstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        (unsigned char*)"</");
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
    
    // dg_forthnewstring(pBHarrayhead);
    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        0,
        (unsigned char*)"");
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
        
    dg_stotoplstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID,
        namelength,
        pname);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
        
    // dg_forthurlencodestring(pBHarrayhead);
    dg_urlencodelstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
        
    // dg_forthcatstring(pBHarrayhead);
    dg_catlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
    
    dg_stotoplstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
		DG_STRINGSTRINGSTACK_BUFFERID,
        2,
        (unsigned char*)">\n");
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hlisttodglumlstringname);
        return;
    }
}


const char* dg_newunsortedhlistelementname = "dg_newunsortedhlistelement";
        
UINT64 dg_newunsortedhlistelement (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    Hlistheader myhlistheader,
    UINT64 parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
    unsigned char* pname,
    UINT64 namelength,
    unsigned char* pvalue,
    UINT64 valuelength,
    UINT64 previouselementid,
    UINT64 nextelementid)
{
    Hlistelementheader myhlistelementheader;
    
    UINT64 elementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    myhlistelementheader.magic = dg_hlistelementmagic;
    myhlistelementheader.parentelementid = parentelementid;
    myhlistelementheader.lastchildelementid = DG_ENDOFLIST;
    myhlistelementheader.firstchildelementid = DG_ENDOFLIST;
    myhlistelementheader.nextsiblingelementid = nextelementid;
    myhlistelementheader.previoussiblingelementid = previouselementid;

    // push the header onto end of freeable lstring array, ingoring
      // any free elements
    elementid = dg_newfreeablelstringonend (
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        (unsigned char*)&myhlistelementheader,
        sizeof(Hlistelementheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newunsortedhlistelementname);
        return (DG_ENDOFLIST);
    }

    // name
    dg_pushlstring (
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid,
        myhlistheader.namelstrstringbufid,
        namelength,
        pname);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newunsortedhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // value
    dg_pushlstring (
        pBHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        myhlistheader.valuelstrstringbufid,
        valuelength,
        pvalue);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newunsortedhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    // child sort keys
    dg_pushlstring (
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        0,
        (unsigned char*)"");
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newunsortedhlistelementname);
        return (DG_ENDOFLIST);
    }
    
    return (elementid);
}


const char* dg_callhlistchildrenname = "dg_callhlistchildren";

void dg_callhlistchildren(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,         // hlist containing function names to do
    UINT64 parentelementid, // parent element id in hlist containing function names to do
    UINT64         fsortedkeyslstringlength,       // function symbol list - actually. the list doesn't
    unsigned char* pfsortedkeyslstring,            //   change at run time so a key array is not necessary
    UINT64*        pfnamelstringoffsetbuffer,
    unsigned char* pfnamelstringstringbuffer,
    void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))
                     // size of the pfunctions array in bytes is the same size as the function name lstring offset buffer
{
    unsigned char* pfunctionname;
    UINT64 functionnamelength;
    unsigned char* pfunctionvalue;
    UINT64 functionvaluelength;
    
    Hlistheader myhlistheader;
    Freeablelstringarrayheader myflstrheader;
    
    Hlistelementheader myparentelementheader;
    Hlistelementheader* pchildelementheader;
    UINT64 childelementheaderlength;
    
    UINT64 sortedkeyslstringlength = 0;

    UINT64 childelementid;
    

    
    UINT64 wherefoundflag, indexofkeyaftermatch, key;
    

    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // go through each child and call it's function
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        hlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
        return;
    }
        
    dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
        return;
    }
    
    // copying parent element ... could get pointer but just in case
    //  in future I add something that modifies the freeable lstring array...
    dg_copysfromlstringn (
        pBHarrayhead,
		myflstrheader.lstringoffsetbufferid,
		myflstrheader.lstringstringbufferid,
		parentelementid, // flstringid,
        0, // offset,
        sizeof(Hlistelementheader),  // length,
        (unsigned char*)&myparentelementheader); // pdest);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
        return;
    }
    
    childelementid = myparentelementheader.firstchildelementid;
    
    while (childelementid != DG_ENDOFLIST)
    {
        // child's name is function to do
        dg_getshlistelement (
            pBHarrayhead,
            hlistid,
            childelementid,
            &pfunctionname,
            &functionnamelength,
            &pfunctionvalue,
            &functionvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
            return;
        }
        
        // find child's name in the symbol table
        wherefoundflag = dg_findsortedhlistchildsub (
            pBHarrayhead,
            pfunctionname,
            functionnamelength,
            fsortedkeyslstringlength,
            pfsortedkeyslstring,
            pfnamelstringoffsetbuffer,
            pfnamelstringstringbuffer,
            &indexofkeyaftermatch, // index in sort key lstring after match
            &key);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
            return;
        }
        
        if (0 != wherefoundflag)
        {
            // The symbol wasn't found. This is an error.
            if (functionnamelength > maxwordlength)
            {
                functionnamelength = maxwordlength;
            }

            dg_putbuffersegment(
                pBHarrayhead,
                DG_DATASPACE_BUFFERID,
                lastnotfoundword,
                functionnamelength,
                pfunctionname);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
                return;
            }

            dg_putbufferbyte(
                pBHarrayhead,
                DG_DATASPACE_BUFFERID,
                lastnotfoundword + functionnamelength,
                0);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
                return;
            }
            
            dg_pusherror(pBHarrayhead, dg_symbolnotfounderror);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
            return;
        }
        
        // call the function
        (*pfunctions[key])(
            pBHarrayhead,
            hlistid,
            childelementid,
            pfunctionvalue,
            functionvaluelength,
            &myhlistheader);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_putbufferuint64(
                pBHarrayhead,
                DG_DATASPACE_BUFFERID,
                dg_callhlisterrorelementid,
                childelementid);
            
            if (functionnamelength > maxwordlength)
            {
                functionnamelength = maxwordlength;
            }

            dg_putbuffersegment(
                pBHarrayhead,
                DG_DATASPACE_BUFFERID,
                lastnotfoundword,
                functionnamelength,
                pfunctionname);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
                return;
            }

            dg_putbufferbyte(
                pBHarrayhead,
                DG_DATASPACE_BUFFERID,
                lastnotfoundword + functionnamelength,
                0);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
                return;
            }
            
            dg_pusherror(pBHarrayhead, dg_errorinsubroutine);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
            return;
        }
        
        pchildelementheader = (Hlistelementheader*)dg_getplstring(
            pBHarrayhead,
            myflstrheader.lstringoffsetbufferid,
            myflstrheader.lstringstringbufferid,
            childelementid,
            &childelementheaderlength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
            return;
        }
        
        if (childelementheaderlength < sizeof(Hlistelementheader))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
            return;
        }
        
        if (pchildelementheader->magic != dg_hlistelementmagic)
        {
            dg_pusherror(pBHarrayhead, dg_badmagicerror);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenname);
            return;
        }
        
        childelementid = pchildelementheader->nextsiblingelementid;
    }
}

const char* dg_callhlistchildrenbynname = "dg_callhlistchildrenbyn";

void dg_callhlistchildrenbyn(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,         // hlist containing indexes of functions 
    UINT64 parentelementid, // parent element id in hlist containing indexes of functions to do
    UINT64 maxnumberoffunctions,
    void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))
                     // size of the pfunctions array in bytes is the same size as the function name lstring offset buffer
{
    unsigned char* pfunctionname;
    UINT64 functionnamelength;
    unsigned char* pfunctionvalue;
    UINT64 functionvaluelength;
    
    Hlistheader myhlistheader;
    Freeablelstringarrayheader myflstrheader;
    
    Hlistelementheader myparentelementheader;
    Hlistelementheader* pchildelementheader;
    UINT64 childelementheaderlength;
    
    UINT64 i, childelementid;
    

    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // go through each child and call it's function
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        hlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
        return;
    }
        
    dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
        return;
    }
    
    // copying parent element ... could get pointer but just in case
    //  in future I add something that modifies the freeable lstring array...
    dg_copysfromlstringn (
        pBHarrayhead,
		myflstrheader.lstringoffsetbufferid,
		myflstrheader.lstringstringbufferid,
		parentelementid, // flstringid,
        0, // offset,
        sizeof(Hlistelementheader),  // length,
        (unsigned char*)&myparentelementheader); // pdest);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
        return;
    }
    
    childelementid = myparentelementheader.firstchildelementid;
    
    while (childelementid != DG_ENDOFLIST)
    {
        // child's name is index of function to do
        dg_getshlistelement (
            pBHarrayhead,
            hlistid,
            childelementid,
            &pfunctionname,
            &functionnamelength,
            &pfunctionvalue,
            &functionvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
            return;
        }
        
        if (functionnamelength < sizeof(UINT64))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
            return;
        }
        
        i = *((UINT64*)pfunctionname);
        
        if (i >= maxnumberoffunctions)
        {
            dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
            return;
        }
        
        // call the function
        (*pfunctions[i])(
            pBHarrayhead,
            hlistid,
            childelementid,
            pfunctionvalue,
            functionvaluelength,
            &myhlistheader);
        
        pchildelementheader = (Hlistelementheader*)dg_getplstring(
            pBHarrayhead,
            myflstrheader.lstringoffsetbufferid,
            myflstrheader.lstringstringbufferid,
            childelementid,
            &childelementheaderlength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
            return;
        }
        
        if (childelementheaderlength < sizeof(Hlistelementheader))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
            return;
        }
        
        if (pchildelementheader->magic != dg_hlistelementmagic)
        {
            dg_pusherror(pBHarrayhead, dg_badmagicerror);
            dg_pusherror(pBHarrayhead, dg_callhlistchildrenbynname);
            return;
        }
        
        childelementid = pchildelementheader->nextsiblingelementid;
    }
}

const char* dg_packedhlistmagicstring = "PackedHlist";
UINT64 dg_packedhlistmagicstringlength = 11;

const char* dg_packhlistname = "dg_packhlist";

UINT64 dg_packhlist (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid)
{
    UINT64 mylstringoffsetbuffer;
    UINT64 mylstringstringbuffer;
    
    Hlistheader myhlistheader;
    Freeablelstringarrayheader myflstrheader;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(dg_badbufferid);
    }
    
    mylstringoffsetbuffer =
        dg_newbuffer (
            pBHarrayhead,
            0x1000,       // growby
            (UINT64)largestunsignedint,   // maxsize,
            &pError,
            FORTH_FALSE); // force out of memory error
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    mylstringstringbuffer =
        dg_newbuffer (
            pBHarrayhead,
            0x10000,       // growby
            (UINT64)largestunsignedint,   // maxsize,
            &pError,
            FORTH_FALSE); // force out of memory error
    
    if (pError != dg_success)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // could use a pointer in this case...
    dg_gethlistheader(
        pBHarrayhead,
        hlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
        
    dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push 'magic' for packed hlist to lstring stack
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        dg_packedhlistmagicstringlength,
        (unsigned char*)dg_packedhlistmagicstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push name offset buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push name string buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myhlistheader.namelstrstringbufid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }

    // push value offset buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push value string buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myhlistheader.valuelstrstringbufid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push sorted keys offset buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push sorted keys string buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myhlistheader.sortedchildidslstrstringbufid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push hlist header freeable lstring offset buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myflstrheader.lstringoffsetbufferid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push hlist header freeable lstring string buffer to lstring stack
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myflstrheader.lstringstringbufferid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength,
        pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // push hlist header freeable lstring free lstring buffer to lstring stack
    //  minus the header
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    if (*pbufferlength < sizeof(Freeablelstringarrayheader))
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer,
        *pbufferlength - sizeof(Freeablelstringarrayheader),
        pbuffer + sizeof(Freeablelstringarrayheader));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    dg_packlstring (
        pBHarrayhead,
        mylstringoffsetbuffer,
        mylstringstringbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_freebuffer (
            pBHarrayhead,
            mylstringoffsetbuffer);
        
        dg_freebuffer (
            pBHarrayhead,
            mylstringstringbuffer);
        
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return(dg_badbufferid);
    }
    
    // mylstringstringbuffer now contains the packed lstring
    
    dg_freebuffer (
        pBHarrayhead,
        mylstringoffsetbuffer);
    
    return (mylstringstringbuffer);
}

const char* dg_unpackhlistname = "dg_unpackhlist";

UINT64 dg_unpackhlist (
    Bufferhandle* pBHarrayhead,
    UINT64 lstringstringbufferid)
{
    
    Hlistheader myhlistheader;
    Freeablelstringarrayheader myflstrheader;
    
    UINT64 lstringoffsetbufferid;
    UINT64 hlistid;
    
    unsigned char* plstring;
    UINT64 lstringlength;
    
    const char* pError;
    INT64 compareresultflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(DG_ENDOFLIST);
    }
    
    lstringoffsetbufferid = dg_unpacklstring (
        pBHarrayhead,
        lstringstringbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        0, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // checking packed hlist magic
    pError = dg_comparebytes(
        plstring,
        lstringlength,
        (unsigned char*)dg_packedhlistmagicstring,
        dg_packedhlistmagicstringlength,
        &compareresultflag);
            
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return (dg_badbufferid);
    }
    
    if (0 != compareresultflag)
    {
        dg_pusherror(pBHarrayhead, dg_badmagicerror);
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return (dg_badbufferid);
    }
    
    // making a new hlist and getting headers
    hlistid = dg_newhlist(pBHarrayhead);
    
    dg_gethlistheader(
        pBHarrayhead,
        hlistid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {        
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
        
    dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myflstrheader,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist name offset buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        1, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist name string buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        2, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myhlistheader.namelstrstringbufid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist value offset buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        3, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myhlistheader.valuelstroffsetbufid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist value string buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        4, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myhlistheader.valuelstrstringbufid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist sorted keys offset buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        5, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist sorted keys string buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        6, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myhlistheader.sortedchildidslstrstringbufid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }

    // get hlist element header freeable lstring offset buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        7, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myflstrheader.lstringoffsetbufferid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist element header freeable lstring string buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        8, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        myflstrheader.lstringstringbufferid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // get hlist element header freeable lstring free list buffer
    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        9, // srcstringid,
        &lstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }
    
    // the correct freeable lstring header should already be in this buffer
    dg_pushbuffersegment (
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        lstringlength,
        plstring);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_unpackhlistname);
        return(dg_badbufferid);
    }

    return (hlistid);
}

const char dg_namestringtovaluestringname[] = "dg_namestringtovaluestring";

unsigned char* dg_namestringtovaluestring(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pname,
    UINT64 namelength,
    UINT64* pvaluelength)
{
    UINT64 wherefoundflag, indexofkeyaftermatch, sortkey;
    unsigned char* pvalue = (unsigned char*)badbufferhandle;
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(pvalue);
    }
    
    pError = dg_putuint64(pvaluelength, 0);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_namestringtovaluestringname);
        return(pvalue);
    }
    
    wherefoundflag = dg_findsortedhlistchild (
        pBHarrayhead,
        pname,
        namelength,
        hlistid,
        elementid,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &sortkey);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namestringtovaluestringname);
        return(pvalue);
    }
    
    if (wherefoundflag != 0)
    {
        dg_pusherror(pBHarrayhead, dg_namenotfounderror);
        dg_pusherror(pBHarrayhead, dg_namestringtovaluestringname);
        return(pvalue); // not found case
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        hlistid,
        sortkey,
        pvaluelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namestringtovaluestringname);
        return(pvalue);
    }
    
    return(pvalue);
}


/*
const char* dg_wordlisttoccodename = "dg_wordlisttoccode";

void dg_wordlisttoccode(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 parentelementid)
{
    // for each child of parent element
      // getting name, nameoffset, value, valueoffset, and generating
      // ccode
    
    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    
    Hlistheader myhlistheader;
    
    UINT64 sortedkeyslstringlength = 0;
    unsigned char* psortedkeyslstring;
    
    UINT64 numberofsortedchildren, i, j, childelementid;
    
    const char* pError;
    
    UINT64 bufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == parentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    bufferid = dg_newbuffer(pBHarrayhead, 0x1000, (UINT64)largestunsignedint, pError, FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_wordlisttoccodename);
        return;
    }
    
    // using this function so that we know the memory at the hlist header is valid
      // except that in this case, the buffer will not move... so we could just
      // get a pointer into the hlist memory instead of copying
    dg_gethlistheader(
        pBHarrayhead,
        hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_wordlisttoccodename);
        return;
    }
    
    psortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        parentelementid,
        &sortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_wordlisttoccodename);
        return;
    }
    
    if ((sortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_wordlisttoccodename);
        return;
    }
    
    numberofsortedchildren = sortedkeyslstringlength >> 3;
    
    if (0 == numberofsortedchildren)
    {
        return;
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        bufferid,
        5,
        (unsigned char*)" = {\n");
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_wordlisttoccodename);
        return;
    }
    
    for(i=0; i < numberofsortedchildren; i++)
    {
        childelementid = ((UINT64*)psortedkeyslstring)[i];
        
        //push the child's name to the string stack to do a dlsym
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            hlistheaderid,
            childelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        dg_pushbuffersegment (
            pBHarrayhead,
            bufferid,
            4,
            (unsigned char*)"    ");
        
        for (j = 0; j < namelength; j++)
        {
            dg_pushbufferbyte(pBHarrayhead, bufferid, '\'');
            if (pname[i] == '\'')
            {
                dg_pushbuffersegment(pBHarrayhead, bufferid, 2, (unsigned char*)"39");
            }
            else
            {
                if (pname[j] == '\\')
                {
                    dg_pushbuffersegment(pBHarrayhead, bufferid, 2, (unsigned char*)"92");
                }
                else
                {
                    dg_pushbufferbyte(pBHarrayhead, bufferid, pname[j]);
                }
            }
            
            dg_pushbufferbyte(pBHarrayhead, bufferid, '\'');
            dg_pushbufferbyte(pBHarrayhead, bufferid, ','');
        }
        
        dg_pushbufferbyte(pBHarrayhead, bufferid, '\n');
        
        // get the child element's value. This is the offset in the buffer to be patched.
        pvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            hlistheaderid,
            childelementid,
            &valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
    }
    
    dg_pushbuffersegment (
        pBHarrayhead,
        bufferid,
        2,
        (unsigned char*)"}\n");
        
    dg_pushdatastack(pBHArrayhead, bufferid);
    
    // push file name to string stack
        
    //dg_forthsavefilestring
}
*/

const char* dg_rootelementname = "root";

const char* dg_symbollistelementname = "symbollist";

const char* dg_importselementname = "imports";

const char* dg_inithlistsname = "dg_inithlists";

void dg_inithlists (Bufferhandle* pBHarrayhead)
{ 
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // reserving hlist 0 for wordlists
    dg_newhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 0 element 0 as root parent element containing all wordlists
    dg_newhlistelement (
        pBHarrayhead,
        0, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_rootelementname, // pname,
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 1 for variable strings
    dg_newhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 1 element 0 as root parent element containing all variables
    dg_newhlistelement (
        pBHarrayhead,
        1, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_rootelementname, // pname,
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 2 for named buffers (linker uses these)
    dg_newhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 2 element 0 as root parent element containing all named buffers
    dg_newhlistelement (
        pBHarrayhead,
        2, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_rootelementname, // pname,
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 3 for symbol lists (for named buffer exports - linker uses these)
    dg_newhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 3 element 0 as root parent element containing all symbol lists
    dg_newhlistelement (
        pBHarrayhead,
        3, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_rootelementname, // pname,
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 4 for list of named shared libraries list
    dg_newhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 4 element 0 as root parent element containing all named shared libraries
    dg_newhlistelement (
        pBHarrayhead,
        4, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_rootelementname, // pname,
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 5 for named hlists list
    dg_newhlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
    
    // reserving hlist 5 element 0 as root parent element containing all named hlists
    dg_newhlistelement (
        pBHarrayhead,
        5, // hlistid,
        DG_ENDOFLIST, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_rootelementname, // pname,
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_inithlistsname);
        return;
    }
}

