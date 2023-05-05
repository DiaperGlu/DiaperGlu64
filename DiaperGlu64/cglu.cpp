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

// ///////////////////////
// Loader Linker Stuff  //
// ///////////////////////

// this routine makes a new buffer and patches a link with the base address
//   <DG_GLUFUNCLINKNEWBUF>
//     <bufferlength>patchoffset</bufferlength>

// gonna switch this to be <patchoffset>bufferlength</>
const char dg_patchpnewbuffername[] = "dg_patchpnewbuffer";

void dg_patchpnewbuffer(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing patch new buffer list
    UINT64 destparentelementid,   // parent element id of the patch new buffer list
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmydesthlistheader)
{
    unsigned char* pvalue;
    UINT64 valuelength;
    
    unsigned char* pchildname;
    UINT64 childnamelength;
    unsigned char* pchildvalue;
    UINT64 childvaluelength;
    
    UINT64 newbufferlength;
    UINT64 destbufferoffset;
    
    UINT64 destnamedbuffer;
    UINT64 destbufferid;
    unsigned char* pdestbuffer;
    UINT64* pdestbufferlength;
    
    UINT64 newbufferid;
    unsigned char* pnewbuffer;
    UINT64* pnewbufferlength;
    
    // Hlistheader myhlistheader;
    
    UINT64 sortedkeyslstringlength = 0;
    unsigned char* psortedkeyslstring;
    
    UINT64 numberofsortedchildren, i, childelementid;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == destparentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    // get pointer to and length of destination named buffer
    destnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        destnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
        return;
    }
    
    destbufferid = *((UINT64*)pvalue);
    
    pdestbuffer = dg_getpbuffer(
        pBHarrayhead,
        destbufferid,
		&pdestbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
        return;
    }
    
    psortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        pmydesthlistheader->sortedchildidslstroffsetbufid,
        pmydesthlistheader->sortedchildidslstrstringbufid,
        destparentelementid,
        &sortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
        return;
    }
    
    if ((sortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
        return;
    }
    
    numberofsortedchildren = sortedkeyslstringlength >> 3;
    
    if (0 == numberofsortedchildren)
    {
        return;
    }
    
    for(i=0; i < numberofsortedchildren; i++)
    {
        childelementid = ((UINT64*)psortedkeyslstring)[i];
        
        dg_getshlistelement (
            pBHarrayhead,
            desthlistheaderid,
            childelementid,
            &pchildname,
            &childnamelength,
            &pchildvalue,
            &childvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
            return;
        }
        
        if (childnamelength < sizeof(UINT64))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
            return;
        }
        
        if (childvaluelength < sizeof(UINT64))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
            return;
        }
        
        newbufferlength = *((UINT64*)(pchildname));
        destbufferoffset = *((UINT64*)(pchildvalue));
        
        // make sure the offset is in the buffer with enough room for patch
        if (destbufferoffset > ((*pdestbufferlength) - sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
            dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
            return;
        }
        
        // make the new buffer
        newbufferid = dg_newbuffer(
            pBHarrayhead,
            newbufferlength,
            newbufferlength,
            &pError,
            FORTH_FALSE);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
            dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
            return;
        }
        
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_LINKNEWBUFFERIDSTACK_BUFFERID,
            newbufferid);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
            return;
        }
        
        dg_growbuffer (
            pBHarrayhead,
            newbufferid,
            newbufferlength,
            &pError,
            FORTH_FALSE);
        
        // can't really get an error here if dg_newbuffer worked
        
        pnewbuffer = dg_getpbuffer(
            pBHarrayhead,
            newbufferid,
            &pnewbufferlength);
        
        // patch the buffer
        //*((UINT64*)(pbuffer + childvalue)) = symbolvalue;
        pError = dg_putuint64(
            (UINT64*)(pdestbuffer+ destbufferoffset),
            (UINT64)pnewbuffer);
        
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
            dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
            return;
        }
    }
}

// this is the key routine :-)
const char dg_patchaddressusingdlsymname[] = "dg_patchaddressusingdlsym";
//const UINT64 dg_patchaddressusingdlsymnlen = 25;

void dg_patchaddressusingdlsym(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,    // id of hlist containing destination patch list
    UINT64 parentelementid,  // parent element id of destination patch list
    UINT64 dylibhandle,      // handle of source shared library
    unsigned char* pbuffer,  // address of destination buffer to patch
    UINT64 bufferlength)     // length of destination buffer
{
    // for each child of parent element
      // searching only symbols in the shared library represented by dylibhandle
      //   dlsym the child element's name to get the address (or number)
      // use the child element's value as an offset into the buffer
      // if the offset targets inside the buffer,
      //   put the address to the offset in the buffer
    
    unsigned char* pname;
    UINT64 namelength;
    UINT64 symbolvalue;
    unsigned char* pvalue;
    UINT64 childvaluelength;
    UINT64 childvalue;
    
    Hlistheader myhlistheader;
    
    UINT64 sortedkeyslstringlength = 0;
    unsigned char* psortedkeyslstring;
    
    UINT64 numberofsortedchildren, i, childelementid;
    
    const char* pError;
    
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
        dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
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
        dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
        return;
    }
    
    if ((sortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
        return;
    }
    
    numberofsortedchildren = sortedkeyslstringlength >> 3;
    
    if (0 == numberofsortedchildren)
    {
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
        
        dg_pushlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            namelength,
            pname);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, dylibhandle);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        // do the dlsym
        dg_forthfindlibrarysymbol(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        // get the symbol value from the data stack
        symbolvalue = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        // need to handle the not found case - dlsym returns null when symbol not found
        if (0 == symbolvalue)
        {
            // The symbol wasn't found. This is an error.
            if (namelength > maxwordlength)
            {
                namelength = maxwordlength;
            }

            dg_putbuffersegment(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword, namelength, pname);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
                return;
            }

            dg_putbufferbyte(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword + namelength, 0);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
                return;
            }
            
            dg_pusherror(pBHarrayhead, dg_symbolnotfounderror);
            
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        // get the child element's value. This is the offset in the buffer to be patched.
        pvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            hlistheaderid,
            childelementid,
            &childvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        if (childvaluelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        childvalue = *((UINT64*)(pvalue));
        
        // make sure the offset is in the buffer with enough room for patch
        if (childvalue > (bufferlength - sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
        
        // patch the buffer
        //*((UINT64*)(pbuffer + childvalue)) = symbolvalue;
        pError = dg_putuint64((UINT64*)(pbuffer+ childvalue), symbolvalue);
        
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
            dg_pusherror(pBHarrayhead, dg_patchaddressusingdlsymname);
            return;
        }
    }
}

const char dg_patchaddressusinghdlsymbname[] = "dg_patchaddressusingdlsymb";

void dg_patchaddressusingdlsymb(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing patch symbol list
    UINT64 destparentelementid,   // parent element id of the patch symbol list
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmydesthlistheader)
{
    UINT64 destnamedbuffer;
    unsigned char* pvalue;
    UINT64 valuelength;
    UINT64 destbufferid;
    unsigned char* pdestbuffer;
    UINT64* pdestbufferlength;
    
    UINT64 srcnamedsharedlibrary;
    UINT64 dylibhandle;
    
    unsigned char* pname;
    UINT64 namelength;
    UINT64 symbolvalue;
    unsigned char* pchildvalue;
    UINT64 childvaluelength;
    UINT64 childvalue;
    
    UINT64 sortedkeyslstringlength = 0;
    unsigned char* psortedkeyslstring;
    
    UINT64 numberofsortedchildren, i, childelementid;
    
    const char* pError;
    
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == destparentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    // get pointer to and length of destination named buffer
    destnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        destnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    destbufferid = *((UINT64*)pvalue);
    
    pdestbuffer = dg_getpbuffer(
        pBHarrayhead,
        destbufferid,
		&pdestbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    // get shared library handle
    srcnamedsharedlibrary = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchsrcnamedlib);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        srcnamedsharedlibrary, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    dylibhandle = *((UINT64*)pvalue);
    
    // dg_patchaddressusingdlsym(
    //    pBHarrayhead,
    //    desthlistheaderid,    // id of hlist containing destination patch list
    //    destparentelementid,  // parent element id of destination patch list
    //    dylibhandle,      // handle of source shared library
    //    pdestbuffer,  // address of destination buffer to patch
    //    *pdestbufferlength);
    
    psortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        pmydesthlistheader->sortedchildidslstroffsetbufid,
        pmydesthlistheader->sortedchildidslstrstringbufid,
        destparentelementid,
        &sortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    if ((sortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
        return;
    }
    
    numberofsortedchildren = sortedkeyslstringlength >> 3;
    
    if (0 == numberofsortedchildren)
    {
        return;
    }
    
    for(i=0; i < numberofsortedchildren; i++)
    {
        childelementid = ((UINT64*)psortedkeyslstring)[i];
        
        //push the child's name to the string stack to do a dlsym
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            desthlistheaderid,
            childelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        dg_pushlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            namelength,
            pname);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, dylibhandle);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        // do the dlsym
        dg_forthfindlibrarysymbol(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        // get the symbol value from the data stack
        symbolvalue = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        // need to handle the not found case - dlsym returns null when symbol not found
        if (0 == symbolvalue)
        {
            // The symbol wasn't found. This is an error.
            if (namelength > maxwordlength)
            {
                namelength = maxwordlength;
            }

            dg_putbuffersegment(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword, namelength, pname);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
                return;
            }

            dg_putbufferbyte(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword + namelength, 0);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
                return;
            }
            
            dg_pusherror(pBHarrayhead, dg_symbolnotfounderror);
            
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        // get the child element's value. This is the offset in the buffer to be patched.
        pchildvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            desthlistheaderid,
            childelementid,
            &childvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        if (childvaluelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        childvalue = *((UINT64*)(pchildvalue));
        
        // make sure the offset is in the buffer with enough room for patch
        if (childvalue > (*pdestbufferlength - sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
        
        // patch the buffer
        //*((UINT64*)(pbuffer + childvalue)) = symbolvalue;
        pError = dg_putuint64((UINT64*)(pdestbuffer+ childvalue), symbolvalue);
        
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghdlsymbname);
            return;
        }
    }
}

const char dg_patchaddressusinghlistname[] = "dg_patchaddressusinghlist";
//const UINT64 dg_patchaddressusinghlistnlen = 25;

void dg_patchaddressusinghlist(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing destination patch list
    UINT64 destparentelementid,   // parent element id of the destination patch list
    unsigned char* pdestbuffer,   // address of destination buffer to patch
    UINT64 destbufferlength,      // length of destination buffer
    UINT64 srchlistheaderid,      // source symbol list hlist
    UINT64 srcparentelementid,    // source symbol list parent element id
    unsigned char* psrcbuffer)    // pointer to source buffer (base address)
{
    // for each child of parent element in the destination hlist
      // search the children of the specified parent in the source hlist
      //   get the value of child element's name and add to source buffer's base address
      // use the destination hlist's child element's value as an offset into the buffer
      // if the offset targets inside the destination buffer,
      //   put the calculated address to the offset into the destination buffer
    
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* pdestvalue;
    UINT64 destchildvaluelength;
    UINT64 destchildvalue;
    
    Hlistheader mydesthlistheader;
    
    UINT64 destsortedkeyslstringlength = 0;
    unsigned char* pdestsortedkeyslstring;
    
    UINT64 destnumberofsortedchildren, i, destchildelementid;
    

    unsigned char* psrcvalue;
    UINT64 srcchildvaluelength;
    UINT64 srcchildvalue;
    UINT64 srcaddress;
    
    UINT64 wherefoundflag, indexofkeyaftermatch, key;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == destparentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    if (DG_ENDOFLIST == srcparentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        desthlistheaderid,
        &mydesthlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
        return;
    }
    
    pdestsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        mydesthlistheader.sortedchildidslstroffsetbufid,
        mydesthlistheader.sortedchildidslstrstringbufid,
        destparentelementid,
        &destsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
        return;
    }
    
    if ((destsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
        return;
    }
    
    destnumberofsortedchildren = destsortedkeyslstringlength >> 3;
    
    if (0 == destnumberofsortedchildren)
    {
        return;
    }
    
    // this patches alphabetically
    for(i=0; i < destnumberofsortedchildren; i++)
    {
        destchildelementid = ((UINT64*)pdestsortedkeyslstring)[i];
        
        // find the child's name in the source hlist
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            desthlistheaderid,
            destchildelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        
        
        wherefoundflag = dg_findsortedhlistchild (
            pBHarrayhead,
            pname,
            namelength,
            srchlistheaderid,
            srcparentelementid,
            &indexofkeyaftermatch, // index in sort key lstring after match
            &key);
        
        if (0 != wherefoundflag)
        {
            // The symbol wasn't found. This is an error.
            if (namelength > maxwordlength)
            {
                namelength = maxwordlength;
            }

            dg_putbuffersegment(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword, namelength, pname);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
                return;
            }

            dg_putbufferbyte(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword + namelength, 0);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
                return;
            }
            
            dg_pusherror(pBHarrayhead, dg_symbolnotfounderror);
            
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        
        // get the source child element's value. This is the offset in the buffer to be patched.
        psrcvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            srchlistheaderid,
            key,
            &srcchildvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        
        if (srcchildvaluelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        
        srcchildvalue = *((UINT64*)(psrcvalue));
        
        /*
        // could make sure the src offset is in the src buffer
        if (childvalue > (destbufferlength - sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        */
        
        srcaddress = (UINT64)(psrcbuffer + srcchildvalue);
        
        
        // get the destination child element's value. This is the offset in the buffer to be patched.
        pdestvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            desthlistheaderid,
            destchildelementid,
            &destchildvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        
        if (destchildvaluelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        
        destchildvalue = *((UINT64*)(pdestvalue));
        
        // make sure the offset is in the buffer with enough room for patch
        if (destchildvalue > (destbufferlength - sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
        
        // patch the buffer
        //*((UINT64*)(pbuffer + childvalue)) = symbolvalue;
        pError = dg_putuint64((UINT64*)(pdestbuffer+ destchildvalue), srcaddress);
        
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
            dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistname);
            return;
        }
    }

}


const char dg_patchaddressusinghlistbname[] = "dg_patchaddressusinghlistb";

void dg_patchaddressusinghlistb(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing patch symbol list
    UINT64 destparentelementid,   // parent element id of the patch symbol list
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmydesthlistheader)
    
{
    // for each child of parent element in the destination hlist
      // search the children of the specified parent in the source hlist
      //   get the value of child element's name and add to source buffer's base address
      // use the destination hlist's child element's value as an offset into the buffer
      // if the offset targets inside the destination buffer,
      //   put the calculated address to the offset into the destination buffer
    UINT64 destnamedbuffer;
    UINT64 srcnamedbuffer;
    UINT64 srcsymbollist;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 destbufferid;
    UINT64 srcbufferid;
    
    unsigned char* pdestbuffer;   // address of destination buffer to patch
    UINT64* pdestbufferlength;      // length of destination buffer
    UINT64 srchlistheaderid;      // source hlist
    UINT64 srcparentelementid;    // should be root... but just in case it's not
    unsigned char* psrcbuffer;    // pointer to source buffer (base address)
    UINT64* psrcbufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == destparentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    // get pointer to and length of destination named buffer
    destnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        destnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    destbufferid = *((UINT64*)pvalue);
    
    pdestbuffer = dg_getpbuffer(
        pBHarrayhead,
        destbufferid,
		&pdestbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    // get pointer to source buffer
    srcnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchsrcnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        srcnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    srcbufferid = *((UINT64*)pvalue);
    
    psrcbuffer = dg_getpbuffer(
        pBHarrayhead,
        srcbufferid,
		&psrcbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    // getting source symbol list hlist id and parent element id
    srcsymbollist = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchsrcnamedsymbollist);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        srcsymbollist, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    if (valuelength < sizeof(HListidElementid)) // going to replace this with generic longlong
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
    
    srchlistheaderid =   ((HListidElementid*)pvalue)->hlistid;
    srcparentelementid = ((HListidElementid*)pvalue)->elementid;
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        srchlistheaderid,
        srcparentelementid, // elementid,
        &valuelength);
    
    dg_patchaddressusinghlist(
        pBHarrayhead,
        desthlistheaderid,     // id of hlist containing destination patch list
        destparentelementid,   // parent element id of the destination patch list
        pdestbuffer,   // address of destination buffer to patch
        *pdestbufferlength,      // length of destination buffer
        srchlistheaderid,      // source symbol list hlist
        srcparentelementid,    // source symbol list parent element id
        psrcbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusinghlistbname);
        return;
    }
}

const char dg_patchaddressusingoffsetname[] = "dg_patchaddressusingoffset";
//const UINT64 dg_patchaddressusinghlistnlen = 25;

void dg_patchaddressusingoffset(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing destination patch list
    UINT64 destparentelementid,   // parent element id of the destination patch list
    unsigned char* pdestbuffer,   // address of destination buffer to patch
    UINT64 destbufferlength,      // length of destination buffer
    unsigned char* psrcbuffer)    // pointer to source buffer (base address)
{
    // for each child of parent element in the destination hlist
      // search the children of the specified parent in the source hlist
      //   get the value of child element's name and add to source buffer's base address
      // use the destination hlist's child element's value as an offset into the buffer
      // if the offset targets inside the destination buffer,
      //   put the calculated address to the offset into the destination buffer
    
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* pdestvalue;
    UINT64 destchildvaluelength;
    UINT64 destchildvalue;
    
    Hlistheader mydesthlistheader;
    
    UINT64 destsortedkeyslstringlength = 0;
    unsigned char* pdestsortedkeyslstring;
    
    UINT64 destnumberofsortedchildren, i, destchildelementid;
    
    UINT64 srcoffset, srcaddress;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == destparentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        desthlistheaderid,
        &mydesthlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
        return;
    }
    
    pdestsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        mydesthlistheader.sortedchildidslstroffsetbufid,
        mydesthlistheader.sortedchildidslstrstringbufid,
        destparentelementid,
        &destsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
        return;
    }
    
    if ((destsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
        return;
    }
    
    destnumberofsortedchildren = destsortedkeyslstringlength >> 3;
    
    if (0 == destnumberofsortedchildren)
    {
        return;
    }
    
    // this patches alphabetically
    for(i=0; i < destnumberofsortedchildren; i++)
    {
        destchildelementid = ((UINT64*)pdestsortedkeyslstring)[i];
        
        // the child's name is the offset in the source buffer (this is backwards I think)
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            desthlistheaderid,
            destchildelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
            return;
        }
        
        if (namelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
            return;
        }
        
        srcoffset = *((UINT64*)(pname));
        
        srcaddress = (UINT64)(psrcbuffer + srcoffset);
        
        
        // get the destination child element's value. This is the offset in the buffer to be patched.
        pdestvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            desthlistheaderid,
            destchildelementid,
            &destchildvaluelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
            return;
        }
        
        if (destchildvaluelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
            return;
        }
        
        destchildvalue = *((UINT64*)(pdestvalue));
        
        // make sure the offset is in the buffer with enough room for patch
        if (destchildvalue > (destbufferlength - sizeof(UINT64)))
        {
            dg_pusherror(pBHarrayhead, dg_segmentgoespastenderror);
            dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
            return;
        }
        
        // patch the buffer
        //*((UINT64*)(pbuffer + childvalue)) = symbolvalue;
        pError = dg_putuint64((UINT64*)(pdestbuffer+ destchildvalue), srcaddress);
        
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_putuint64name);
            dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetname);
            return;
        }
    }
}


// I'm thinking this one should use only one buffer for both src and dest
//  and it should be the patchdestbuf
const char dg_patchaddressusingoffsetbname[] = "dg_patchaddressusingoffsetb";

void dg_patchaddressusingoffsetb(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing patch symbol list
    UINT64 destparentelementid,   // parent element id of the patch symbol list
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmydesthlistheader)
    
{
    // for each child of parent element in the destination hlist
      // search the children of the specified parent in the source hlist
      //   get the value of child element's name and add to source buffer's base address
      // use the destination hlist's child element's value as an offset into the buffer
      // if the offset targets inside the destination buffer,
      //   put the calculated address to the offset into the destination buffer
    UINT64 destnamedbuffer;
    UINT64 srcnamedbuffer;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 destbufferid;
    UINT64 srcbufferid;
    
    unsigned char* pdestbuffer;   // address of destination buffer to patch
    UINT64* pdestbufferlength;      // length of destination buffer

    unsigned char* psrcbuffer;    // pointer to source buffer (base address)
    UINT64* psrcbufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (DG_ENDOFLIST == destparentelementid)
    {
        // can't search list of root elements ... yet ... so...
        return;
    }
    
    // get pointer to and length of destination named buffer
    destnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        destnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    destbufferid = *((UINT64*)pvalue);
    
    pdestbuffer = dg_getpbuffer(
        pBHarrayhead,
        destbufferid,
		&pdestbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    // get pointer to source buffer
    srcnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchsrcnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        srcnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    srcbufferid = *((UINT64*)pvalue);
    
    psrcbuffer = dg_getpbuffer(
        pBHarrayhead,
        srcbufferid,
		&psrcbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
    
    dg_patchaddressusingoffset(
        pBHarrayhead,
        desthlistheaderid,     // id of hlist containing destination patch list
        destparentelementid,   // parent element id of the destination patch list
        pdestbuffer,   // address of destination buffer to patch
        *pdestbufferlength,      // length of destination buffer
        psrcbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchaddressusingoffsetbname);
        return;
    }
}

const char dg_diaperglulibsymbolname[] = "dglib";

const char dg_diaperglulibname[] = DG_DIAPERGLU_LIB_NAME;

// <loadsharedliblist>
//  <namedbuffername1>libfilename1
//  <namedbuffername2>libfilename2
// </loadsharedliblist>
const char dg_loadsharedliblistname[] = "dg_loadsharedliblist";

void dg_loadsharedliblist(
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 parentelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader)
{
    unsigned char* psrcsortedkeyslstring;
    UINT64 srcsortedkeyslstringlength;
    
    UINT64 numberoflibstoimport;
    UINT64 srclibelementid;
    
    UINT64 i, x;
    
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    const char* pError;
    INT64 compareresultflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    psrcsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        pmysrchlistheader->sortedchildidslstroffsetbufid,
        pmysrchlistheader->sortedchildidslstrstringbufid,
        parentelementid,
        &srcsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
        return;
    }
    
    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
        return;
    }
    
    numberoflibstoimport = srcsortedkeyslstringlength >> 3;
    
    if (0 == numberoflibstoimport)
    {
        return;
    }
    
    for(i=0; i < numberoflibstoimport; i++)
    {
        srclibelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // get the child's name and value in the source hlist
          // name is named buffer name to use
          // value is the name of the shared library to load
        dg_getshlistelement (
            pBHarrayhead,
            srchlistid,
            srclibelementid,
            &pname,
            &namelength,
            &pvalue,
            &valuelength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
            return;
        }
        
        pError = dg_comparebytes(
            pvalue,
            valuelength,
            (unsigned char*)dg_diaperglulibsymbolname,
            sizeof(dg_diaperglulibsymbolname) - 1, // to drop null terminator
            &compareresultflag);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, dg_comparebytesname);
            dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
            return;
        }
    
        if (0 == compareresultflag)
        {
            pvalue = (unsigned char*)dg_diaperglulibname;
            valuelength = sizeof(dg_diaperglulibname) - 1;
        }
        
        // open the shared library
        dg_pushlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            valuelength,
            pvalue);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
            return;
        }
        
        dg_forthloadlibrarystringsub(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
            return;
        }
        
        // get the handle from the top of the open library handle stack
        x = dg_getuint64stackelement (
            pBHarrayhead,
            DG_LIBHANDLE_BUFFERID,
            0); // index
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
            return;
        }
        
        // add the shared library to the named shared library list
        dg_newhlistelement (
            pBHarrayhead,
            DG_NAMEDSHAREDLIBS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pname,      // name of symbol list
            namelength, // length of symbol list name,
            (unsigned char*)&x, // pvalue,
            sizeof(UINT64)); // valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != 0)
        {
            dg_pusherror(pBHarrayhead, dg_loadsharedliblistname);
            return;
        }
    }
}

// <loadfilelist>
//  <namedbuffername1>filename1
//  <namedbuffername2>filename2
// </loadfilelist>
const char dg_loadfilelistname[] = "dg_loadfilelist";

void dg_loadfilelist(
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 parentelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader)
{
    unsigned char* psrcsortedkeyslstring;
    UINT64 srcsortedkeyslstringlength;
    
    UINT64 numberoffilestoimport;
    UINT64 srcfileelementid;
    
    UINT64 i;
    
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 namedbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    psrcsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        pmysrchlistheader->sortedchildidslstroffsetbufid,
        pmysrchlistheader->sortedchildidslstrstringbufid,
        parentelementid,
        &srcsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_loadfilelistname);
        return;
    }
    
    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_loadfilelistname);
        return;
    }
    
    numberoffilestoimport = srcsortedkeyslstringlength >> 3;
    
    if (0 == numberoffilestoimport)
    {
        return;
    }
    
    for(i=0; i < numberoffilestoimport; i++)
    {
        srcfileelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // get the child's name and value in the source hlist
          // name is named buffer name to use
          // value is the name of the file to load
        dg_getshlistelement (
            pBHarrayhead,
            srchlistid,
            srcfileelementid,
            &pname,
            &namelength,
            &pvalue,
            &valuelength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadfilelistname);
            return;
        }
        
        // load the file
        dg_pushlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            valuelength,
            pvalue);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadfilelistname);
            return;
        }
        
        dg_forthloadfilestring(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadfilelistname);
            return;
        }
        
        namedbufferid = dg_popdatastack(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadfilelistname);
            return;
        }
        
        // add the file to the named buffer list
        dg_newhlistelement (
            pBHarrayhead,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pname,      // name of symbol list
            namelength, // length of symbol list name,
            (unsigned char*)&namedbufferid, // pvalue,
            sizeof(UINT64)); // valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadfilelistname);
            return;
        }
    }
}

// <loadhlistfilelist>
//  <namedhlistname1>filename1
//  <namedhlistname2>filename2
// </loadhlistfilelist>
const char dg_loadhlistfilelistname[] = "dg_loadhlistfilelist";

void dg_loadhlistfilelist(
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 parentelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader)
{
    unsigned char* psrcsortedkeyslstring;
    UINT64 srcsortedkeyslstringlength;
    
    UINT64 numberoffilestoimport;
    UINT64 srcfileelementid;
    
    UINT64 i;
    
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 packedhlistbufferid;
    UINT64 unpackedhlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    psrcsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        pmysrchlistheader->sortedchildidslstroffsetbufid,
        pmysrchlistheader->sortedchildidslstrstringbufid,
        parentelementid,
        &srcsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
        return;
    }
    
    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
        return;
    }
    
    numberoffilestoimport = srcsortedkeyslstringlength >> 3;
    
    if (0 == numberoffilestoimport)
    {
        return;
    }
    
    for(i=0; i < numberoffilestoimport; i++)
    {
        srcfileelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // get the child's name and value in the source hlist
          // name is named buffer name to use
          // value is the name of the file to load
        dg_getshlistelement (
            pBHarrayhead,
            srchlistid,
            srcfileelementid,
            &pname,
            &namelength,
            &pvalue,
            &valuelength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
            return;
        }
        
        // load the file
        dg_pushlstring(
            pBHarrayhead,
            DG_STRINGOFFSETSTACK_BUFFERID,
            DG_STRINGSTRINGSTACK_BUFFERID,
            valuelength,
            pvalue);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
            return;
        }
        
        dg_forthloadfilestring(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
            return;
        }
        
        packedhlistbufferid = dg_popdatastack(pBHarrayhead);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
            return;
        }
        
        unpackedhlistid = dg_unpackhlist (
            pBHarrayhead,
            packedhlistbufferid);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
            return;
        }
        
        // add the file to the named hlist list
        dg_newhlistelement (
            pBHarrayhead,
            DG_NAMEDHLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pname,      // name of symbol list
            namelength, // length of symbol list name,
            (unsigned char*)&unpackedhlistid, // pvalue,
            sizeof(UINT64)); // valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_loadhlistfilelistname);
            return;
        }
    }
}

// <DG_BUFFERS>
//  <buffername1>buffersize1
//  <buffername2>buffersize2
// </DG_BUFFERS>



const char dg_newbufferlistname[] = "dg_newbufferlist";

void dg_newbufferlist(
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 parentelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader)
{
    unsigned char* psrcsortedkeyslstring;
    UINT64 srcsortedkeyslstringlength;
    
    UINT64 numberofbufferstomake;
    UINT64 bufferelementid;
    
    UINT64 i;
    
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 namedbufferid;
    UINT64 buffersize;

    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    psrcsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        pmysrchlistheader->sortedchildidslstroffsetbufid,
        pmysrchlistheader->sortedchildidslstrstringbufid,
        parentelementid,
        &srcsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_newbufferlistname);
        return;
    }
    
    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_newbufferlistname);
        return;
    }
    
    numberofbufferstomake = srcsortedkeyslstringlength >> 3;
    
    if (0 == numberofbufferstomake)
    {
        return;
    }
    
    for(i=0; i < numberofbufferstomake; i++)
    {
        bufferelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // get the child's name and value in the source hlist
          // name is named buffer name to use
          // value is the name of the file to load
        dg_getshlistelement (
            pBHarrayhead,
            srchlistid,
            bufferelementid,
            &pname,
            &namelength,
            &pvalue,
            &valuelength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_newbufferlistname);
            return;
        }
        
        // value is size of buffer
        //  allocated size will be rounded up to nearest system page size
        /*
        buffersize = dg_hexdectonumber(pvalue, valuelength, &flag);
        
        if (flag != FORTH_TRUE)
        {
            // string not convertable to number error
            dg_pusherror(pBHarrayhead, dg_invalidparametererror);
            dg_pusherror(pBHarrayhead, dg_hexdectonumbername);
            dg_pusherror(pBHarrayhead, dg_newbufferlistname);
            return;
        }
        */
        
        if (valuelength < sizeof(UINT64))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_newbufferlistname);
        }
        
        buffersize = *((UINT64*)pvalue);
                
        // make the new buffer
        namedbufferid = dg_newbuffer(pBHarrayhead, buffersize, buffersize, &pError, FORTH_FALSE);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
            dg_pusherror(pBHarrayhead, dg_newbufferlistname);
            return;
        }
        
        dg_growbuffer (
            pBHarrayhead,
            namedbufferid,
            buffersize,
            &pError,
            FORTH_FALSE);
        
        // can't really get an error here if dg_newbuffer worked
        
        // add the buffer to the named buffer list
        dg_newhlistelement (
            pBHarrayhead,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pname,      // name of symbol list
            namelength, // length of symbol list name,
            (unsigned char*)&namedbufferid, // pvalue,
            sizeof(UINT64)); // valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_newbufferlistname);
            return;
        }
    }
}

/*
const char dg_valuetonewbufferlistname[] = "dg_valuetonewbufferlist";

void dg_valuetonewbufferlist(
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 parentelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader)
{
    unsigned char* psrcsortedkeyslstring;
    UINT64 srcsortedkeyslstringlength;
    
    UINT64 numberofbufferstomake;
    UINT64 bufferelementid;
    
    UINT64 i;
    
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 namedbufferid;

    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    psrcsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        pmysrchlistheader->sortedchildidslstroffsetbufid,
        pmysrchlistheader->sortedchildidslstrstringbufid,
        parentelementid,
        &srcsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_valuetonewbufferlistname);
        return;
    }
    
    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_valuetonewbufferlistname);
        return;
    }
    
    numberofbufferstomake = srcsortedkeyslstringlength >> 3;
    
    if (0 == numberofbufferstomake)
    {
        return;
    }
    
    for(i=0; i < numberofbufferstomake; i++)
    {
        bufferelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // get the child's name and value in the source hlist
          // name is named buffer name to use
          // value is the name of the file to load
        dg_getshlistelement (
            pBHarrayhead,
            srchlistid,
            bufferelementid,
            &pname,
            &namelength,
            &pvalue,
            &valuelength);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_valuetonewbufferlistname);
            return;
        }
                
        // make the new buffer
        namedbufferid = dg_newbuffer(
            pBHarrayhead,
            valuelength,
            valuelength,
            &pError,
            FORTH_FALSE);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_newbuffername);
            dg_pusherror(pBHarrayhead, dg_valuetonewbufferlistname);
            return;
        }
        
        dg_pushbuffersegment (
            pBHarrayhead,
            namedbufferid,
            valuelength,
            pvalue);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_valuetonewbufferlistname);
            return;
        }
        
        // add the buffer to the named buffer list
        dg_newhlistelement (
            pBHarrayhead,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // parentelementid,
            pname,      // name of named buffer
            namelength, // length of named buffer's name,
            (unsigned char*)&namedbufferid, // pvalue,
            sizeof(UINT64)); // valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_valuetonewbufferlistname);
            return;
        }
    }
}
*/

// adds current element in current hlist to list of symbol lists
// <symbollist>symbollistname
//   <symbolname1>value1
//   <symbolname2>value2
// </symbollist>

const char dg_loadsymbollistname[] = "dg_loadsymbollist";

void dg_loadsymbollist(
    Bufferhandle* pBHarrayhead,
    UINT64 symbollisthlistid,
    UINT64 symbollistelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader)
{
    unsigned char* pvalue;
    UINT64 valuelength;
    
    struct HListidElementid symbollistparent;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    symbollistparent.hlistid = symbollisthlistid;
    symbollistparent.elementid = symbollistelementid;
    
    // need pointer to the value of current element
    //  which is the symbol list's name
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        symbollisthlistid, // hlistheaderid,
        symbollistelementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_loadsymbollistname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // parentelementid,
        pvalue,      // name of symbol list
        valuelength, // length of symbol list name,
        (unsigned char*)&symbollistparent, // pvalue,
        sizeof(HListidElementid)); // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_loadsymbollistname);
        return;
    }
}

// <destinationpatchbuffer>namedbuffername</destinationpatchbuffer>
const char dg_setpatchdestbufidname[] = "dg_setpatchdestbufid";

void dg_setpatchdestbufid (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pbuffername,
    UINT64 buffernamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedbufferelementid = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            pbuffername,
            buffernamelength,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedbufferelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchdestbufidname);
        return;
    }
    
    dg_putbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedbuf,
        namedbufferelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchdestbufidname);
        return;
    }
}


// <sourcepatchbuffer>namebuffername</sourcepatchbuffer>
const char dg_setpatchsrcbufidname[] = "dg_setpatchsrcbufid";

void dg_setpatchsrcbufid (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pbuffername,
    UINT64 buffernamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedbufferelementid = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            pbuffername,
            buffernamelength,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedbufferelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchsrcbufidname);
        return;
    }
    
    dg_putbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedbuf,
        namedbufferelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchsrcbufidname);
        return;
    }
}

// <sourcepatchdylib>nameddylibname</sourcepatchdylib>
const char dg_setpatchsrclibname[] = "dg_setpatchsrclib";

void dg_setpatchsrclib (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* plibname,
    UINT64 libnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedlibraryelementid = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            plibname,
            libnamelength,
            DG_NAMEDSHAREDLIBS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedlibraryelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchsrclibname);
        return;
    }
    
    dg_putbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedlib,
        namedlibraryelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchsrclibname);
        return;
    }
}

// <sourcepatchsymbollist>namedsymbollistname</sourcepatchsymbollist>
const char dg_setpatchsrcsymbollistname[] = "dg_setpatchsrcsymbollist";

void dg_setpatchsrcsymbollist (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* psymbollistname,
    UINT64 symbollistnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedsymbollistelementid = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            psymbollistname,
            symbollistnamelength,
            DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedsymbollistelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchsrcsymbollistname);
        return;
    }
    
    dg_putbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchsrcnamedsymbollist,
        namedsymbollistelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchsrcsymbollistname);
        return;
    }
}

const char dg_setpatchdestsymbollistname[] = "dg_setpatchdestsymbollist";

void dg_setpatchdestsymbollist (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* psymbollistname,
    UINT64 symbollistnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedsymbollistelementid = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            psymbollistname,
            symbollistnamelength,
            DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedsymbollistelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchdestsymbollistname);
        return;
    }
    
    dg_putbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_patchdestnamedsymbollist,
        namedsymbollistelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_setpatchdestsymbollistname);
        return;
    }
}


// If you need to call with less parameters, such as a dglu script call, or with no parameters, just
//  use this function. The extra parameters on the return stack won't make a difference except that
//  pushing the extra parameters takes a little bit of time.
const char dg_callpatchsrclibname[] = "dg_callpatchsrclib";

UINT64 dg_callpatchsrclib (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pfunctionname,
    UINT64 functionnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 srcnamedsharedlibrary;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 dylibhandle;
    UINT64 symbolvalue;
    UINT64 (*pfunction)(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 elementid);
    
    UINT64 result = (UINT64)largestunsignedint;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(result);
    }
    
    // get shared library handle
    srcnamedsharedlibrary = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchsrcnamedlib);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibname);
        return(result);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDSHAREDLIBS_HLISTID,
        srcnamedsharedlibrary, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibname);
        return(result);
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibname);
        return(result);
    }
    
    dylibhandle = *((UINT64*)pvalue);
    
    dg_pushlstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        functionnamelength,
        pfunctionname);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibname);
        return(result);
    }
        
    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, dylibhandle);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibname);
        return(result);
    }
        
    // do the dlsym
    dg_forthfindlibrarysymbol(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibname);
        return(result);
    }
        
    // get the symbol value from the data stack
    symbolvalue = dg_popbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibname);
        return(result);
    }
    
    pfunction = (UINT64 (*)(Bufferhandle*, UINT64, UINT64)) symbolvalue;
    
    result = (*pfunction)(pBHarrayhead, hlistid, elementid);
    
    return(result);
}

const char dg_callpatchsrclibtodsname[] = "dg_callpatchsrclibtods";

void dg_callpatchsrclibtods (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pfunctionname,
    UINT64 functionnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_callpatchsrclib (
        pBHarrayhead,
        hlistid,
        elementid,
        pfunctionname,
        functionnamelength,
        pmyhlistheader);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibtodsname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, x);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrclibtodsname);
        return;
    }
}


// If you need to call with less parameters, such as a dglu script call, or with no parameters, just
//  use this function. The extra parameters on the return stack won't make a difference except that
//  pushing the extra parameters takes a little bit of time.
const char dg_callpatchsrcbufsymbolname[] = "dg_callpatchsrcbufsymbol";

UINT64 dg_callpatchsrcbufsymbol (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pfunctionname,
    UINT64 functionnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 srcnamedsymbollist;
    UINT64 srcnamedbuffer;
    
    UINT64 srcbufferid;
    
    UINT64 srcbufferoffset;
    
    UINT64 namelength;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    HListidElementid* pmysrcsymbollist;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 wherefoundflag, indexofkeyaftermatch, key;
    
    UINT64 (*pfunction)(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 elementid);
    
    UINT64 result = (UINT64)largestunsignedint;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(result);
    }
    
    // get symbol list hlist id and element id
    srcnamedsymbollist = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchsrcnamedsymbollist);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        srcnamedsymbollist, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    if (valuelength < sizeof(HListidElementid))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    pmysrcsymbollist = (HListidElementid*)pvalue;
    
    wherefoundflag = dg_findsortedhlistchild (
        pBHarrayhead,
        pfunctionname,
        functionnamelength,
        pmysrcsymbollist->hlistid,
        pmysrcsymbollist->elementid,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &key);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
        
    if (0 != wherefoundflag)
    {
        namelength = functionnamelength;
        
        if (namelength > maxwordlength)
        {
            namelength = maxwordlength;
        }

        dg_putbuffersegment(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword, namelength, pfunctionname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
            return(result);
        }

        dg_putbufferbyte(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword + namelength, 0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
            return(result);
        }
        
        dg_pusherror(pBHarrayhead, dg_symbolnotfounderror);
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        pmysrcsymbollist->hlistid,
        key, // elementid,
        &valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    srcbufferoffset = *((UINT64*)pvalue);
    
    // get pointer to dest buffer
    srcnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchsrcnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        srcnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    srcbufferid = *((UINT64*)pvalue);
    
    pbuffer = dg_getpbuffer (
        pBHarrayhead,
        srcbufferid,
		&pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymbolname);
        return(result);
    }
    
    // value is offset in buffer
    pfunction = (UINT64 (*)(Bufferhandle*, UINT64, UINT64))(pbuffer + srcbufferoffset);
    
    result = (*pfunction)(pBHarrayhead, hlistid, elementid);
    
    return (result);
}

const char dg_callpatchsrcbufsymboltodsname[] = "dg_callpatchsrcbufsymboltods";

void dg_callpatchsrcbufsymboltods (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pfunctionname,
    UINT64 functionnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_callpatchsrcbufsymbol (
        pBHarrayhead,
        hlistid,
        elementid,
        pfunctionname,
        functionnamelength,
        pmyhlistheader);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymboltodsname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, x);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchsrcbufsymboltodsname);
        return;
    }
}


// If you need to call with less parameters, such as a dglu script call, or with no parameters, just
//  use this function. The extra parameters on the return stack won't make a difference except that
//  pushing the extra parameters takes a little bit of time.
const char dg_callpatchdestbufoffsetname[] = "dg_callpatchdestbufoffset";

UINT64 dg_callpatchdestbufoffset (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pdestoffset,
    UINT64 destoffsetlength,
    Hlistheader* pmyhlistheader)
{
    UINT64 destnamedbuffer;
    
    UINT64 destbufferid;
    
    UINT64 destbufferoffset;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    unsigned char* pbuffer;
    UINT64* pbufferlength;
    
    UINT64 (*pfunction)(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 elementid);
    
    UINT64 result = (UINT64)largestunsignedint;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return(result);
    }
    
    if (destoffsetlength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_callpatchdestbufoffsetname);
        return(result);
    }
    
    destbufferoffset = *((UINT64*)pdestoffset);
    
    // get pointer to dest buffer
    destnamedbuffer = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
		dg_patchdestnamedbuf);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchdestbufoffsetname);
        return(result);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        destnamedbuffer, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchdestbufoffsetname);
        return(result);
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_callpatchdestbufoffsetname);
        return(result);
    }
    
    destbufferid = *((UINT64*)pvalue);
    
    pbuffer = dg_getpbuffer (
        pBHarrayhead,
        destbufferid,
		&pbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchdestbufoffsetname);
        return(result);
    }
    
    // value is offset in buffer
    pfunction = (UINT64 (*)(Bufferhandle*, UINT64, UINT64))(pbuffer + destbufferoffset);
    
    result = (*pfunction)(pBHarrayhead, hlistid, elementid);
    
    return (result);
}


const char dg_callpatchdestbufoffsttodsname[] = "dg_callpatchdestbufoffsttods";

void dg_callpatchdestbufoffsttods (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pfunctionname,
    UINT64 functionnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 x;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_callpatchdestbufoffset (
        pBHarrayhead,
        hlistid,
        elementid,
        pfunctionname,
        functionnamelength,
        pmyhlistheader);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchdestbufoffsttodsname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, x);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_callpatchdestbufoffsttodsname);
        return;
    }
}


const char dg_glueidhidtodsname[] = "dg_glueidhidtods";

void dg_glueidhidtods (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pfunctionname,
    UINT64 functionnamelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, elementid);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_glueidhidtodsname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, hlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_glueidhidtodsname);
        return;
    }
}

const char dg_gluuint64valuetodsname[] = "dg_gluuint64valuetods";

void dg_gluuint64valuetods (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pvalue,
    UINT64 valuelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_gluuint64valuetodsname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, *((UINT64*)pvalue));
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_gluuint64valuetodsname);
        return;
    }
}

const char dg_gluvaluetossname[] = "dg_gluvaluetoss";

void dg_gluvaluetoss (
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid,
    UINT64 elementid,
    unsigned char* pvalue,
    UINT64 valuelength,
    Hlistheader* pmyhlistheader)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushlstring(pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		valuelength,
		pvalue);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_gluvaluetossname);
        return;
    }
}

// <NGlu>namedhlistname</NGlu>
const char dg_glufuncngluname[] = "dg_glufuncnglu";

void dg_glufuncnglu(
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 parentelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader)
{
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 namedhlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // find the hlist in the named hlist list
      // dg_namestringtovaluestring
    // do nglu on the hlist
    pvalue = dg_namestringtovaluestring(
        pBHarrayhead,
        DG_NAMEDHLISTS_HLISTID,
        DG_ROOT_ELEMENTID,
        pparentvalue,       // unsigned char* pname,
        parentvaluelength,  // UINT64 namelength,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_glufuncngluname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_glufuncngluname);
        return;
    }
    
    namedhlistid = *((UINT64*)pvalue);
    
    dg_callhlistchildrenbyn(
        pBHarrayhead,
        namedhlistid,         // hlist containing function names to do
        DG_ROOT_ELEMENTID, // parent element id in hlist containing function names to do
        dg_numberofglufunctions,
        (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_glufuncngluname);
        return;
    }
    
}

// glu hlist root element name
const char dg_glulistelementname[] = "Glu ";
UINT64 dg_glulistelementnamelength = 4;

const char dg_nglulistelementname[] = "NGlu";
UINT64 dg_nglulistelementnamelength = 4;

// glu hlist function element names (glu function names)

const char dg_bufferseleementname[] = "Bufs";
UINT64 dg_bufferselementnamelength = 4; // 4

const char dg_calldestbufname[] = "CallBuf";
UINT64 dg_calldestbufnamelength = 7; // 11

const char dg_calldestbuftodsname[] = "CallBufToDS";
UINT64 dg_calldestbuftodsnamelength = 11; // 22

const char dg_calldestoffsetname[] = "CallDestOffset";
UINT64 dg_calldestoffsetnamelength = 14; // 36

const char dg_calldestoffsettodsname[] = "CallDestOffsetToDS";
UINT64 dg_calldestoffsetnametodslength = 18; // 54

const char dg_calllibname[] = "CallLib";
UINT64 dg_calllibnamelength = 7; // 61

const char dg_calllibtodsname[] = "CallLibToDS";
UINT64 dg_calllibtodsnamelength = 11; // 72

const char dg_setdestbufname[] = "DestBuf";
UINT64 dg_setdestbufnamelength = 7; // 79

const char dg_setdestsymbollistname[] = "DestSymbols";
UINT64 dg_setdestsymbollistnamelength = 11; // 90

const char dg_fileselementname[] = "Files";
UINT64 dg_fileselementnamelength = 5; // 95

const char dg_hlistfileselementname[]  = "HFiles";
UINT64 dg_hlistfileselementnamelength = 6; // 101

const char dg_hlistherename[] = "HlistHere";
UINT64 dg_hlistherenamelength = 9; // 110

const char dg_libsname[] = "Libs";
UINT64 dg_libsnamelength = 4; // 114

const char dg_linkbufname[] = "LinkBuf";
UINT64 dg_linkbufnamelength = 7; // 121

const char dg_linklibname[] = "LinkLib";
UINT64 dg_linklibnamelength = 7; // 128

const char dg_linknewbufname[] = "LinkNewBuf";
UINT64 dg_linknewbufnamelength = 10; // 138

const char dg_linkoffsetname[] = "LinkOffset";
UINT64 dg_linkoffsetnamelength = 10; // 148

const char dg_ngluname[] = "NGlu";
UINT64 dg_nglunamelength = 4; // 152

const char dg_setsrcbufname[] = "SrcBuf";
UINT64 dg_setsrcbufnamelength = 6; // 158

const char dg_setsrclibname[] = "SrcLib";
UINT64 dg_setsrclibnamelength = 6; // 164

const char dg_setsrcsymbollistname[] = "SrcSymbols";
UINT64 dg_setsrcsymbollistnamelength = 10; // 174

const char dg_symbolsname[] = "Symbols";
UINT64 dg_symbolsnamelength = 7; // 181

const char dg_uint64valuetodsname[] = "UINT64ValueToDS";
UINT64 dg_uint64valuetodsnamelength = 15; // 196

const char dg_valuetostrsname[] = "ValueTo$S";
UINT64 dg_valuetostrsnamelength = 9; // 205



// this isn't a full hlist, this is just the data needed for the find sub
// unsigned char* dg_linkfunctionnames = (unsigned char*)
//    "BufsCallBufCallBufToDSCallLibCallLibToDSDestBufDestSymbolsFilesHlistHereLibsLinkBufLinkLibSrcBufSrcLibSrcSymbolsSymbolsUINT64ValueToDSValueToSS";

unsigned char dg_glufunctionnames[] = {
    'B','u','f','s',
    'C','a','l','l','B','u','f',
    'C','a','l','l','B','u','f','T','o','D','S',
    'C','a','l','l','D','e','s','t','O','f','f','s','e','t',
    'C','a','l','l','D','e','s','t','O','f','f','s','e','t','T','o','D','S',
    'C','a','l','l','L','i','b',
    'C','a','l','l','L','i','b','T','o','D','S',
    'D','e','s','t','B','u','f',
    'D','e','s','t','S','y','m','b','o','l','s',
    'F','i','l','e','s',
    'H','F','i','l','e','s',
    'H','l','i','s','t','H','e','r','e',
    'L','i','b','s',
    'L','i','n','k','B','u','f',
    'L','i','n','k','L','i','b',
    'L','i','n','k','N','e','w','B','u','f',
    'L','i','n','k','O','f','f','s','e','t',
    'N','G','l','u',
    'S','r','c','B','u','f',
    'S','r','c','L','i','b',
    'S','r','c','S','y','m','b','o','l','s',
    'S','y','m','b','o','l','s',
    'U','I','N','T','6','4','V','a','l','u','e','T','o','D','S',
    'V','a','l','u','e','T','o','$','S'};


UINT64 dg_glufunctionnameoffsets[dg_numberofglufunctions] = {
    4,
    11,
    22,
    36,
    54,
    61,
    72,
    79,
    90,
    95,
    101,
    110,
    114,
    121,
    128,
    138,
    148,
    152,
    158,
    164,
    174,
    181,
    196,
    205};

UINT64 dg_glufunctiontable[dg_numberofglufunctions] = {
    (UINT64)&dg_newbufferlist,
    (UINT64)&dg_callpatchsrcbufsymbol,
    (UINT64)&dg_callpatchsrcbufsymboltods,
    (UINT64)&dg_callpatchdestbufoffset,
    (UINT64)&dg_callpatchdestbufoffsttods,
    (UINT64)&dg_callpatchsrclib, // dg_callpatchsrclibsymbol
    (UINT64)&dg_callpatchsrclibtods, // dg_callpatchsrclibsymboltods
    (UINT64)&dg_setpatchdestbufid, // dg_setpatchdestnamedbufid
    (UINT64)&dg_setpatchdestsymbollist, // dg_setpatchdestnamedsymbollist
    (UINT64)&dg_loadfilelist, // dg_loadfiletonamedbufferlist
    (UINT64)&dg_loadhlistfilelist, // dg_loadhlisttonamedhlistlist
    (UINT64)&dg_glueidhidtods,
    (UINT64)&dg_loadsharedliblist, // dg_loadlibtonamedliblist
    (UINT64)&dg_patchaddressusinghlistb,
    (UINT64)&dg_patchaddressusingdlsymb,
    (UINT64)&dg_patchpnewbuffer,
    (UINT64)&dg_patchaddressusingoffsetb,
    (UINT64)&dg_glufuncnglu,
    // dg_gluefuncglu
    (UINT64)&dg_setpatchsrcbufid, // dg_setpatchsrcnamedbufid
    (UINT64)&dg_setpatchsrclib, // dg_setpatchsrcnamedlibid
    (UINT64)&dg_setpatchsrcsymbollist, // dg_setpatchsrcnamedsymbollistid
    (UINT64)&dg_loadsymbollist, // dg_loadsymbollisttonamedsymbollistlist
    (UINT64)&dg_gluuint64valuetods,
    (UINT64)&dg_gluvaluetoss};

UINT64 dg_glufunctionsortedkeys[dg_numberofglufunctions] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23};


const char dg_gluname[] = "dg_glu";

void dg_glu(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid)
{
    unsigned char* pname;
    UINT64 namelength;
    
    const char* pError;
    INT64 compareresultflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // if root element's name is "NGlu", then do an NGlu instead
    //  4 characters in length, no null terminator
    pname = dg_getshlistelementnom (
        pBHarrayhead,
        hlistheaderid,
        DG_ROOT_ELEMENTID,
        &namelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gluname);
        return;
    }
    
    pError = dg_comparebytes(
        pname,
        namelength,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength,
        &compareresultflag);
            
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_gluname);
        return;
    }
    
    if (0 == compareresultflag)
    {
        dg_callhlistchildrenbyn(
            pBHarrayhead,
            hlistheaderid,     // hlist containing function names to do
            DG_ROOT_ELEMENTID, // parent element id in hlist containing function names to do
            dg_numberofglufunctions,
            (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_ngluname);
            dg_pusherror(pBHarrayhead, dg_gluname);
            return;
        }
        
        return;
    }
    
    pError = dg_comparebytes(
        pname,
        namelength,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength,
        &compareresultflag);
            
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_gluname);
        return;
    }
    
    if (0 != compareresultflag)
    {
        dg_pusherror(pBHarrayhead, dg_glulisttypenotfounderror);
        dg_pusherror(pBHarrayhead, dg_gluname);
        return;
    }
    
    dg_callhlistchildren(
        pBHarrayhead,
        hlistheaderid,       // hlist containing function names to do
        DG_ROOT_ELEMENTID,   // parent element id in hlist containing function names to do
        dg_numberofglufunctions * sizeof(UINT64),    // UINT64         fsortedkeyslstringlength,
        (unsigned char*)dg_glufunctionsortedkeys, // unsigned char* pfsortedkeyslstring,
        dg_glufunctionnameoffsets, // UINT64*        pfnamelstringoffsetbuffer,
        dg_glufunctionnames,        // unsigned char* pfnamelstringstringbuffer,
        (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable); // void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_gluname);
        return;
    }
}


void dg_nglu(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid)
{
    unsigned char* pname;
    UINT64 namelength;
    
    const char* pError;
    INT64 compareresultflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // if root element's name is "Glu ", then do an Glu instead
    //  4 characters in length, no null terminator
    pname = dg_getshlistelementnom (
        pBHarrayhead,
        hlistid,
        DG_ROOT_ELEMENTID,
        &namelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ngluname);
        return;
    }
    
    pError = dg_comparebytes(
        pname,
        namelength,
        (unsigned char*)dg_glulistelementname,
        dg_glulistelementnamelength,
        &compareresultflag);
            
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_ngluname);
        return;
    }
    
    if (0 == compareresultflag)
    {
        dg_callhlistchildren(
            pBHarrayhead,
            hlistid,             // hlist containing function names to do
            DG_ROOT_ELEMENTID,   // parent element id in hlist containing function names to do
            dg_numberofglufunctions * sizeof(UINT64),    // UINT64         fsortedkeyslstringlength,
            (unsigned char*)dg_glufunctionsortedkeys, // unsigned char* pfsortedkeyslstring,
            dg_glufunctionnameoffsets, // UINT64*        pfnamelstringoffsetbuffer,
            dg_glufunctionnames,        // unsigned char* pfnamelstringstringbuffer,
            (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable); // void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_gluname);
            dg_pusherror(pBHarrayhead, dg_ngluname);
            return;
        }
        
        return;
    }
    
    pError = dg_comparebytes(
        pname,
        namelength,
        (unsigned char*)dg_nglulistelementname,
        dg_nglulistelementnamelength,
        &compareresultflag);
            
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_comparebytesname);
        dg_pusherror(pBHarrayhead, dg_ngluname);
        return;
    }
    
    if (0 != compareresultflag)
    {
        dg_pusherror(pBHarrayhead, dg_glulisttypenotfounderror);
        dg_pusherror(pBHarrayhead, dg_ngluname);
        return;
    }
    
    dg_callhlistchildrenbyn(
        pBHarrayhead,
        hlistid,           // hlist containing function names to do
        DG_ROOT_ELEMENTID, // parent element id in hlist containing function names to do
        dg_numberofglufunctions,
        (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_ngluname);
        return;
    }
}


const char dg_getnamedsymbollisthideidname[] = "dg_getnamedsymbollisthideid";

UINT64 dg_getnamedsymbollisthideid (
    Bufferhandle* pBHarrayhead,
    unsigned char* psymbollistname,
    UINT64 symbollistnamelength,
    UINT64* phlistid)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedsymbollistelementid = 0;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)largestunsignedint);
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            psymbollistname,
            symbollistnamelength,
            DG_NAMEDSYMBOLLISTS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedsymbollistelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getnamedsymbollisthideidname);
        return ((UINT64)largestunsignedint);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        namedsymbollistelementid, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_patchpnewbuffername);
        return ((UINT64)largestunsignedint);
    }
    
    if (valuelength < sizeof(HListidElementid))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_getnamedsymbollisthideidname);
        return ((UINT64)largestunsignedint);
    }
    
    *phlistid = ((struct HListidElementid*)(pvalue))->hlistid;
    
    return (((struct HListidElementid*)(pvalue))->elementid);
    
}


const char dg_namedbufnametoeidname[] = "dg_namedbufnametoeid";

UINT64 dg_namedbufnametoeid (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedbufferelementid = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    compareresultflag = dg_findsortedhlistchild (
        pBHarrayhead,
        pbuffername,
        buffernamelength,
        DG_NAMEDBUFFERS_HLISTID, // hlistid,
        DG_ROOT_ELEMENTID, // 0 = root
        &indexofkeyaftermatch, // index in sort key lstring after match
        &namedbufferelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametoeidname);
        return (DG_ENDOFLIST);
    }
    
    return (namedbufferelementid);
}


const char* dg_namedbufnametobufidname = "dg_namedbufnametobufid";

UINT64 dg_namedbufnametobufid (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedbufferelementid = 0;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 destbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (dg_badbufferid);
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            pbuffername,
            buffernamelength,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedbufferelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametobufidname);
        return (dg_badbufferid);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        namedbufferelementid, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametobufidname);
        return (dg_badbufferid);
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametobufidname);
        return (dg_badbufferid);
    }
    
    destbufferid = *((UINT64*)pvalue);
    
    return (destbufferid);
}


const char* dg_namedbufnametoaddrname = "dg_namedbufnametoaddr";

unsigned char* dg_namedbufnametoaddr (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 namedbufferelementid = 0;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 destbufferid;
    unsigned char* pdestbuffer;
    UINT64* pdestbufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((unsigned char*)badbufferhandle);
    }
    
    compareresultflag = dg_findsortedhlistchild (
            pBHarrayhead,
            pbuffername,
            buffernamelength,
            DG_NAMEDBUFFERS_HLISTID, // hlistid,
            DG_ROOT_ELEMENTID, // 0 = root
            &indexofkeyaftermatch, // index in sort key lstring after match
            &namedbufferelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametoaddrname);
        return ((unsigned char*)badbufferhandle);
    }
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        namedbufferelementid, // elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametoaddrname);
        return ((unsigned char*)badbufferhandle);
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametoaddrname);
        return ((unsigned char*)badbufferhandle);
    }
    
    destbufferid = *((UINT64*)pvalue);
    
    pdestbuffer = dg_getpbuffer(
        pBHarrayhead,
        destbufferid,
		&pdestbufferlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_namedbufnametoaddrname);
        return ((unsigned char*)badbufferhandle);
    }
    
    return (pdestbuffer);
}

const char* dg_hsymbolnametovaluename = "dg_hsymbolnametovalue";

UINT64 dg_hsymbolnametovalue (
    Bufferhandle* pBHarrayhead,
    unsigned char* psymbolname,
    UINT64 symbolnamelength,
    UINT64 namedsymbollisthlistid,
    UINT64 namedsymbollistelementid)
{
    UINT64 compareresultflag = (UINT64)largestunsignedint;
    UINT64 indexofkeyaftermatch = 0;
    UINT64 symbolelementid = 0;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return ((UINT64)largestunsignedint);
    }
    
    compareresultflag = dg_findsortedhlistchild (
        pBHarrayhead,
        psymbolname,
        symbolnamelength,
        namedsymbollisthlistid,
        namedsymbollistelementid,
        &indexofkeyaftermatch, // index in sort key lstring after match
        &symbolelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hsymbolnametovaluename);
        return ((UINT64)largestunsignedint);
    }
        
    if (0 != compareresultflag)
    {
        dg_pusherror(pBHarrayhead, dg_symbolnotfounderror);
        dg_pusherror(pBHarrayhead, dg_hsymbolnametovaluename);
        return ((UINT64)largestunsignedint);
    }
        
    
    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        namedsymbollisthlistid,
        symbolelementid,
        &valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_hsymbolnametovaluename);
        return ((UINT64)largestunsignedint);
    }
        
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_hsymbolnametovaluename);
        return ((UINT64)largestunsignedint);
    }
        
    return(*((UINT64*)(pvalue)));
}

// dg_findnamedsymboloffset
// dg_findnamedsymbolvalue

// add push chold value strings to named new buffers
//  this will allow compile code buffers to be included in the glu/nglu hlist :-)
// could add children to new lstring array
// could add children to new hlist

// now all I need is a way to make a program that loads and initializes dglu,
//  then loads (or has included) the glu list and calls nglu on the glu list...
// so how do I do this from axxembly?


