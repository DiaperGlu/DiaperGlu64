// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.12.
//
//    DiaperGlu v5.12 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.12 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.12; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 24, 2023              //
// version 5.12               //
// /////////////////////////////



#include "diapergluforth.h"


void dg_forthgluelement(Bufferhandle* pBHarrayhead)
{
    UINT64 hlistid, elementid; // hlist id and parent element id of glu list
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgluelementname);
        return;
    }
    
    // could check that parent element name is "Glu "
    
    elementid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgluelementname);
        return;
    }
    
    dg_callhlistchildren(
        pBHarrayhead,
        hlistid,       // hlist containing function names to do
        elementid,   // parent element id in hlist containing function names to do
        dg_numberofglufunctions * sizeof(UINT64),    // UINT64         fsortedkeyslstringlength,
        (unsigned char*)dg_glufunctionsortedkeys, // unsigned char* pfsortedkeyslstring,
        dg_glufunctionnameoffsets, // UINT64*        pfnamelstringoffsetbuffer,
        dg_glufunctionnames,        // unsigned char* pfnamelstringstringbuffer,
        (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable); // void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgluelementname);
        return;
    }
}


void dg_forthngluelement(Bufferhandle* pBHarrayhead)
{
    UINT64 hlistid, elementid; // hlist id and parent element id of glu list
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthngluelementname);
        return;
    }
    
    // could check that parent element name is "Glu "
    
    elementid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthngluelementname);
        return;
    }
    
    dg_callhlistchildrenbyn(
        pBHarrayhead,
        hlistid,         // hlist containing function names to do
        elementid, // parent element id in hlist containing function names to do
        dg_numberofglufunctions,
        (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthngluelementname);
        return;
    }
}


void dg_forthglu(Bufferhandle* pBHarrayhead)
{
    UINT64 hlistid;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgluname);
        return;
    }
    
    dg_glu(
        pBHarrayhead,
        hlistid);
    
    // could check that root element name is "Glu "
    /*
    dg_callhlistchildren(
        pBHarrayhead,
        hlistid,       // hlist containing function names to do
        DG_ROOT_ELEMENTID,   // parent element id in hlist containing function names to do
        dg_numberofglufunctions * sizeof(UINT64),    // UINT64         fsortedkeyslstringlength,
        (unsigned char*)dg_glufunctionsortedkeys, // unsigned char* pfsortedkeyslstring,
        dg_glufunctionnameoffsets, // UINT64*        pfnamelstringoffsetbuffer,
        dg_glufunctionnames,        // unsigned char* pfnamelstringstringbuffer,
        (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable); // void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*));
    */
    
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgluname);
        return;
    }
}


void dg_forthnglu(Bufferhandle* pBHarrayhead)
{
    UINT64 hlistid;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthngluname);
        return;
    }
    
    dg_nglu(
        pBHarrayhead,
        hlistid);
    
    /*
    dg_callhlistchildrenbyn(
        pBHarrayhead,
        hlistid,         // hlist containing function names to do
        DG_ROOT_ELEMENTID, // parent element id in hlist containing function names to do
        dg_numberofglufunctions,
        (void (**) (Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*))dg_glufunctiontable);
     */
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthngluname);
        return;
    }
}


void dg_forthnewnglulist(Bufferhandle* pBHarrayhead)
//     ( -- gluhlistid )
{
    UINT64 myhlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    myhlistid = dg_newhlist (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglulistname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myhlistid,
        (UINT64)largestunsignedint, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_nglulistelementname,   // unsigned char* pname,
        dg_nglulistelementnamelength,             // UINT64 namelength,
        (unsigned char*)"", // unsigned char* pvalue,
        0); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglulistname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        myhlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglulistname);
        return;
    }
}


void dg_forthnewcurrentnglulist(Bufferhandle* pBHarrayhead)
//     ( -- )
{
    UINT64 myhlistid, myrootelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    myhlistid = dg_newhlist (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewcurrentnglulistname);
        return;
    }
    
    myrootelementid = dg_newhlistelement (
        pBHarrayhead,
        myhlistid,
        (UINT64)largestunsignedint, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_nglulistelementname,   // unsigned char* pname,
        dg_nglulistelementnamelength,             // UINT64 namelength,
        (unsigned char*)"", // unsigned char* pvalue,
        0); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewcurrentnglulistname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        myrootelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewcurrentnglulistname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        myhlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewcurrentnglulistname);
        return;
    }
}

const char dg_createlinkcommaname[] = "dg_createlinkcomma";

void dg_createlinkcomma(
    Bufferhandle* pBHarrayhead,
    UINT64 compiletyperoutine,
    UINT64 linktype) // 0 = data, 1 = code, 2 = none, 3 = raw
{
    UINT64 namelength = 0;
    
    UINT64 ccwordlist;
    UINT64 definition;
    
    UINT64 myhlistid;
    UINT64 mylinklistelementid;
    UINT64 importoffset, linkoffset;
    UINT64 mycurrentcompilebufferid;
    
    UINT64* phstacklength;
    unsigned char* phstack;
    
    unsigned char* pname;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (linktype > 3)
    {
        dg_pusherror(pBHarrayhead, dg_invalidparametererror);
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }

    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    mylinklistelementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
    
    mycurrentcompilebufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }
    
    linkoffset = dg_getbufferlength(
        pBHarrayhead,
        mycurrentcompilebufferid);
    
    importoffset = linkoffset;
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }
    
    // could find the symbol so the link is valid as soon as it's compiled
    
    if (3 == linktype)
    {
        dg_compilesegment(
            pBHarrayhead,
            (const char*)"\0\0\0\0\0\0\0\0",
            8);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
            return;
        }
    }
    else
    {
        importoffset++;
        dg_compilemovntorax(pBHarrayhead, 0);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
            return;
        }
    
        if (0 == linktype)
        {
            dg_compilereturn(pBHarrayhead);
        }
        
        if (2 == linktype)
        {
            dg_compilejumptorax(pBHarrayhead);
        }
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
            return;
        }
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myhlistid,             // hlistid
        mylinklistelementid,   // parentelementid,
        pname, // pcib + ciboldoffset,    // unsigned char* pname,
        namelength,        // UINT64 namelength,
        (unsigned char*)&importoffset,   // unsigned char* pvalue,
        sizeof(UINT64));           // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }
    
    definition = dg_newwordcopyname(
        pBHarrayhead, 
        (UINT64)DG_CORE_BUFFERID,         // compile type routine buffer
        compiletyperoutine,  // compile type routine offset
        mycurrentcompilebufferid,                  // data buffer id which is current compile buffer
        linkoffset,            // data offset which is current compile offset
        (UINT64)DG_CORE_BUFFERID,
        (UINT64)pname, // (pcib + ciboldoffset),
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }
    
    ccwordlist = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentcreatewordlistname);
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }

    dg_linkdefinition(
        pBHarrayhead,
        ccwordlist,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createlinkcommaname);
        return;
    }
}


void dg_forthcreateimportcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypecall,
        2);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateimportcommaname);
        return;
    }
}


void dg_forthcreatecodelinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypecall,
        1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatecodelinkcommaname);
        return;
    }
}

void dg_forthcreateocodelinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypedpushn,
        0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateocodelinkcommaname);
        return;
    }
}

void dg_forthcreateobcodelinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypedpushdn,
        0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateobcodelinkcommaname);
        return;
    }
}

void dg_forthcreatecdecllinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypecdecl,
        1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatecdecllinkcommaname);
        return;
    }
}

void dg_forthcreatecolonlinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypesubroutine,
        1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreatecolonlinkcommaname);
        return;
    }
}

void dg_forthcreateodatalinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypedpushn,
        0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateodatalinkcommaname);
        return;
    }
}

void dg_forthcreateobdatalinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_createlinkcomma(
        pBHarrayhead,
        (UINT64)&dg_forthdocompiletypedpushdn,
        0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcreateobdatalinkcommaname);
        return;
    }
}


void dg_forthwtoimportcomma(Bufferhandle* pBHarrayhead)
{
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )

    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 myhlistid;
    UINT64 mylinklistelementid;
    UINT64 x;
    UINT64 mycurrentcompilebufferid;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pname = dg_parseword(pBHarrayhead, &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthwtoimportcommaname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwtoimportcommaname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthwtoimportcommaname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    mylinklistelementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
  
    
    mycurrentcompilebufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtoimportcommaname);
        return;
    }
    
    x = dg_getbufferlength(
        pBHarrayhead,
        mycurrentcompilebufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtoimportcommaname);
        return;
    }
    
    // could find the symbol so the link is valid as soon as it's compiled
    
    dg_compilesegment(
        pBHarrayhead,
        (const char*)"\0\0\0\0\0\0\0\0",
        8);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtoimportcommaname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myhlistid,             // hlistid
        mylinklistelementid,   // parentelementid,
        pname, // pcib + ciboldoffset,    // unsigned char* pname,
        namelength,        // UINT64 namelength,
        (unsigned char*)&x,   // unsigned char* pvalue,
        sizeof(UINT64));           // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtoimportcommaname);
        return;
    }
}


void dg_forthwtolinkcomma(Bufferhandle* pBHarrayhead)
{
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )

    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 myhlistid;
    UINT64 mylinklistelementid;
    UINT64 x;
    UINT64 mycurrentcompilebufferid;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pname = dg_parseword(pBHarrayhead, &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthwtolinkcommaname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthwtolinkcommaname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthwtolinkcommaname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    mylinklistelementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
  
    
    mycurrentcompilebufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtolinkcommaname);
        return;
    }
    
    x = 1 + dg_getbufferlength(
        pBHarrayhead,
        mycurrentcompilebufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtolinkcommaname);
        return;
    }
    
    // could find the symbol so the link is valid as soon as it's compiled
    
    dg_compilemovntorax(pBHarrayhead, 0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtolinkcommaname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myhlistid,             // hlistid
        mylinklistelementid,   // parentelementid,
        pname, // pcib + ciboldoffset,    // unsigned char* pname,
        namelength,        // UINT64 namelength,
        (unsigned char*)&x,   // unsigned char* pvalue,
        sizeof(UINT64));           // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtolinkcommaname);
        return;
    }
}

void dg_forthwtocodelinkcomma(Bufferhandle* pBHarrayhead)
{
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
  
    dg_forthwtolinkcomma(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtocodelinkcommaname);
        return;
    }
  
    dg_compilejumptorax(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtocodelinkcommaname);
        return;
    }
}

void dg_forthwtodatalinkcomma(Bufferhandle* pBHarrayhead)
{
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
  
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthwtolinkcomma(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtodatalinkcommaname);
        return;
    }
  
    dg_compilereturn(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthwtodatalinkcommaname);
        return;
    }
}



/*
const char dg_forthnewnglubufnamedstrname[] = "NEW-NGLU-BUFFER-NAMED$";

void dg_forthnewnglubufnamedstr(Bufferhandle* pBHarrayhead)
{
    UINT64 mynewbufferid;
    UINT64 mystringstackdepth;
    
    unsigned char* pnamestring;
    UINT64 namestringlength;
    
    UINT64 myngluhlistid;
    UINT64 myfileselementid;
    
    UINT64 x;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    mystringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }

    if (mystringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }

    pnamestring = dg_getplstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        string2id - 1,
        &namestringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    
    // make new named buffer
    mynewbufferid = dg_newbuffer (
        pBHarrayhead,
        dg_defaultbuffergrowby,
        dg_defaultbuffermaxsize,
        &pError,
        FALSE); // orceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer,
        mynewbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        DG_NAMEDBUFFERS_HLISTID,
        DG_ROOT_ELEMENTID, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)pnamestring,   // unsigned char* pname,
        namestringlength,             // UINT64 namelength,
        (unsigned char*)&mynewbufferid, // unsigned char* pvalue,
        sizeof(UINT64)); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    
    myngluhlistid = dg_newhlist (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myngluhlistid,
        (UINT64)largestunsignedint, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)dg_nglulistelementname,   // unsigned char* pname,
        dg_nglulistelementnamelength,             // UINT64 namelength,
        (unsigned char*)"", // unsigned char* pvalue,
        0); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    
    x = DG_GLUFUNCFILES;
    
    myfileselementid = dg_newhlistelement (
        pBHarrayhead,
        myngluhlistid,
        DG_ROOT_ELEMENTID, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)&x,   // unsigned char* pname,
        sizeof(UINT64),             // UINT64 namelength,
        (unsigned char*)"", // unsigned char* pvalue,
        0); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    */
    /*
    dg_newhlistelement (
        pBHarrayhead,
        DG_NAMEDHLISTS_HLISTID,
        myfileselementid, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)pnamestring,   // unsigned char* pname,
        namestringlength,             // UINT64 namelength,
        (unsigned char*) file name goes here, // unsigned char* pvalue,
        file name length goes here); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    */
    /*
    x = DG_GLUFUNCDESTBUF;
    
    dg_newhlistelement (
        pBHarrayhead,
        myngluhlistid,
        DG_ROOT_ELEMENTID, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        (unsigned char*)&x,   // unsigned char* pname,
        sizeof(UINT64),             // UINT64 namelength,
        (unsigned char*)pnamestring, // unsigned char* pvalue,
        namestringlength); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewnglubufnamedstrname);
        return;
    }
    
    
    
    // add command to set current dest buffer to new named buffer
    
}
*/

const char dg_stringtoglulinkcommaname[] = "dg_stringtoglulinkcomma";

void dg_stringtoglulinkcomma(
    Bufferhandle* pBHarrayhead,
    UINT64 linktype) // 0 = return value, 1 = jump to value, 2 = none, 3 = raw
{
    // ( -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )

    UINT64 mystringstackdepth;
    
    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 myhlistid;
    UINT64 mylinklistelementid;
    UINT64 x;
    UINT64 mycurrentcompilebufferid;
    
    UINT64* phstacklength;
    unsigned char* phstack;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    if (linktype > 3)
    {
        dg_pusherror(pBHarrayhead, dg_invalidparametererror);
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
    
    mystringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }

    if (mystringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }

    pname = dg_getplstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        mystringstackdepth - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    mylinklistelementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
    
    mycurrentcompilebufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
    
    x = dg_getbufferlength(
        pBHarrayhead,
        mycurrentcompilebufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
    
    // could find the symbol so the link is valid as soon as it's compiled
    
    if (3 != linktype)
    {
        x++;
        dg_compilemovntorax(pBHarrayhead, 0);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
            return;
        }
    }
    else
    {
        dg_compilesegment(
            pBHarrayhead,
            (const char*)"\0\0\0\0\0\0\0\0",
            8);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
            return;
        }
        
    }
    
    if (0 == linktype)
    {
        dg_compilereturn(pBHarrayhead);
    }
    
    if (1 == linktype)
    {
        dg_compilejumptorax(pBHarrayhead);
    }
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myhlistid,             // hlistid
        mylinklistelementid,   // parentelementid,
        pname,    // unsigned char* pname,
        namelength,        // UINT64 namelength,
        (unsigned char*)&x,   // unsigned char* pvalue,
        sizeof(UINT64));           // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_stringtoglulinkcommaname);
        return;
    }
}


void dg_forthstrtoimportcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_stringtoglulinkcomma(
        pBHarrayhead,
        3); // linktype);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstrtoimportcommaname);
        return;
    }
}


void dg_forthstrtolinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_stringtoglulinkcomma(
        pBHarrayhead,
        2); // linktype);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstrtolinkcommaname);
        return;
    }
}

void dg_forthstrtocodelinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_stringtoglulinkcomma(
        pBHarrayhead,
        1); // linktype);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstrtocodelinkcommaname);
        return;
    }
}

void dg_forthstrtodatalinkcomma(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_stringtoglulinkcomma(
        pBHarrayhead,
        0); // linktype);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstrtodatalinkcommaname);
        return;
    }
}


void dg_forthsymbolsstringtoeh (Bufferhandle* pBHarrayhead)
{
    UINT64 mystringstackdepth;
    
    unsigned char* pnamestring;
    UINT64 namestringlength;
    
    UINT64 myhlistid;
    UINT64 myelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    mystringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolsstringtoehname);
        return;
    }

    if (mystringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsymbolsstringtoehname);
        return;
    }

    pnamestring = dg_getplstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        mystringstackdepth - 1,
        &namestringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolsstringtoehname);
        return;
    }
    
    myelementid = dg_getnamedsymbollisthideid (
        pBHarrayhead,
        pnamestring,
        namestringlength,
        &myhlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolsstringtoehname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        myelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolsstringtoehname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        myhlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolsstringtoehname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
}


void dg_forthnamedbufstringtoe (Bufferhandle* pBHarrayhead)
{
    UINT64 mystringstackdepth;
    
    unsigned char* pnamestring;
    UINT64 namestringlength;
    
    UINT64 myelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    mystringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstringtoename);
        return;
    }

    if (mystringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstringtoename);
        return;
    }

    pnamestring = dg_getplstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        mystringstackdepth - 1,
        &namestringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstringtoename);
        return;
    }
    
    myelementid = dg_namedbufnametoeid (
        pBHarrayhead,
        pnamestring,
        namestringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstringtoename);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        myelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstringtoename);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
}


void dg_forthnamedbufstrtobufid (Bufferhandle* pBHarrayhead)
{
    UINT64 mystringstackdepth;
    
    unsigned char* pnamestring;
    UINT64 namestringlength;
    
    UINT64 mybufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    mystringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtobufidname);
        return;
    }

    if (mystringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtobufidname);
        return;
    }

    pnamestring = dg_getplstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        mystringstackdepth - 1,
        &namestringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtobufidname);
        return;
    }
    
    mybufferid = dg_namedbufnametobufid (
        pBHarrayhead,
        pnamestring,
        namestringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtobufidname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        mybufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtobufidname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
}


void dg_forthnamedbufstrtop (Bufferhandle* pBHarrayhead)
{
    UINT64 mystringstackdepth;
    
    unsigned char* pnamestring;
    UINT64 namestringlength;
    
    unsigned char* pbuffer;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    mystringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtopname);
        return;
    }

    if (mystringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtopname);
        return;
    }

    pnamestring = dg_getplstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        mystringstackdepth - 1,
        &namestringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtopname);
        return;
    }
    
    pbuffer = dg_namedbufnametoaddr (
        pBHarrayhead,
        pnamestring,
        namestringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtopname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)pbuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamedbufstrtopname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
}

void dg_forthhsymbolstrto (Bufferhandle* pBHarrayhead)
{
    UINT64 mystringstackdepth;
    
    unsigned char* pnamestring;
    UINT64 namestringlength;
    
    UINT64 namedsymbollisthlistid;
    UINT64 namedsymbollistelementid;
    
    UINT64 value;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    namedsymbollisthlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhsymbolstrtoname);
        return;
    }
    
    namedsymbollistelementid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhsymbolstrtoname);
        return;
    }
    
    mystringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhsymbolstrtoname);
        return;
    }

    if (mystringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthhsymbolstrtoname);
        return;
    }

    pnamestring = dg_getplstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        mystringstackdepth - 1,
        &namestringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhsymbolstrtoname);
        return;
    }
    
    value = dg_hsymbolnametovalue (
        pBHarrayhead,
        pnamestring,
        namestringlength,
        namedsymbollisthlistid,
        namedsymbollistelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhsymbolstrtoname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        value);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhsymbolstrtoname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
}






