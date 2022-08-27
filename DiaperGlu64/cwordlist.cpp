// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.7.
//
//    DiaperGlu v5.7 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.7 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.7; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// August 26, 2022            //
// version 5.7                //
// /////////////////////////////


#include "diapergluforth.h"


// //////////////////////
// Word List Commands  //
// //////////////////////


// wordlist types

//  standard wordlist: binary insertion sorted symbols
//   search returns word's element id .... need to get
//   cfob pfob from value string maybe should return element id hlist id

//  presorted wordlist: read only
//   search routine returns index in cfob pfob array

//  symbol list: binary insertion sorted symbols with name value string pairs
//   search routine returns index of value string
//   element id hlist id of value string returned... this is pfob
//   cfob is set for entire symbol list... all symbols have same compile type

//  shared libraries: read only name value = UINT64 pairs
//   pfo = value pfb = ignored (is core-buffer-id)
//   cfob is shared for entire library... all symbols have same compile type



// converting to use hlists:
//  a wordlist will just be another word that acts like a constant except it has children
//  it will be up to the words that use a wordlist id to look for children
//  so essentially any word could have children...
const char* dg_newwordlistname = "dg_newwordlist";

UINT64 dg_newwordlist (
    Bufferhandle* pBHarrayhead,
    UINT64 parentelementid)
{
//    UINT64 bufferlength = 0;
    UINT64 wordlistid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(DG_MAX_WORDLISTID);
    }
    
    wordlistid = dg_newhlistelement (
        pBHarrayhead,
        DG_WORDLISTS_HLISTID,  // hlistid, hlist 0 is reserved for wordlists
        parentelementid,       // element 0 root is reserved for parent of wordlist elements
        (unsigned char*)"WORDLIST", // pname,
        8, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength)
        
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newwordlistname);
        return(DG_MAX_WORDLISTID);
    }
    
    return (wordlistid);
}


// creates a new word but does not link it into a wordlist... so it goes at the same level as root
const char* dg_newwordname = "dg_newword";

UINT64 dg_newword (
    Bufferhandle* pBHarrayhead,
    UINT64 compilebufid, 
    UINT64 compilebufoffset,
    UINT64 databufid,
    UINT64 databufoffset,
    UINT64 namebufid,
    UINT64 nameoffset,
    UINT64 namelength)
{
    Definitionheader newdefinition;
    
    unsigned char* pname;
    
    UINT64 wordid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    newdefinition.compileroutinebuf = compilebufid;
    newdefinition.compileroutineoffset = compilebufoffset;
    newdefinition.databuf = databufid;
    newdefinition.dataoffset = databufoffset;
    
    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(DG_ENDOFWORDLIST);
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_newwordname);
        return(DG_ENDOFWORDLIST);
    }

    if (namelength > maxwordlength)
    {
        dg_pusherror(pBHarrayhead, dg_maxwordlengthexceedederror);
        dg_pusherror(pBHarrayhead, dg_newwordname);
        return(DG_ENDOFWORDLIST);
    }
    
    pname = dg_getpbufferoffset  (
        pBHarrayhead,
        namebufid,
        nameoffset);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newwordname);
        return(DG_ENDOFWORDLIST);
    }
    
    wordid = dg_newhlistelement (
        pBHarrayhead,
        DG_WORDLISTS_HLISTID,           // hlistid, hlist 0 reserved for wordlists
        DG_ENDOFLIST,                   // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        pname,
        namelength,
        (unsigned char*)&newdefinition, // pvalue,
        sizeof(Definitionheader)        // valuelength);
    );
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newwordname);
        return(DG_ENDOFWORDLIST);
    }
    
    // I moved this somewhere else for some reason but I can't remember why...
      // putting this elsewhere breaks DOES> and RECURSE
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_latestnewword,
        wordid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newwordname);
        return(DG_ENDOFWORDLIST);
    }
    
    return (wordid);
}

//   base routine will copy name so this will no longer be needed
const char* dg_newwordcopynamename = "dg_newwordcopyname";

UINT64 dg_newwordcopyname (
    Bufferhandle* pBHarrayhead,
    UINT64 compilebufid,
    UINT64 compilebufoffset,
    UINT64 databufid,
    UINT64 databufoffset,
    UINT64 namebufid,
    UINT64 nameoffset,
    UINT64 namelength)
{
    UINT64 wordid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFWORDLIST);
    }
    
    wordid = dg_newword (
        pBHarrayhead,
        compilebufid, 
        compilebufoffset,
        databufid,
        databufoffset,
        namebufid,
        nameoffset,
        namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newwordcopynamename);
        return (DG_ENDOFWORDLIST);
    }
    
    return (wordid);
}


// converting to use hlists:
//  ok this will be the same
UINT64 dg_new0stringnamecoreword (
    Bufferhandle* pBHarrayhead, 
    UINT64 compilebufoffset,
    UINT64 databufoffset,
    unsigned char* pname)
{
    UINT64 namelength = largestsignedint;

    const char* perror;

    // get length of name
    perror = dg_scanforbyte((void*)pname, &namelength, 0);

    if (perror != dg_success)
    {
        // ignoring errors for now, just not putting word in wordlist
        return(DG_ENDOFWORDLIST);
    }

    return(
        dg_newword(
            pBHarrayhead,
            DG_CORE_BUFFERID,
            compilebufoffset,
            DG_CORE_BUFFERID,
            databufoffset,
            DG_CORE_BUFFERID,
            (UINT64)pname,
            namelength)
    );
}


UINT64 dg_new0stringcorenameword (
    Bufferhandle* pBHarrayhead, 
    UINT64 compilebufid, 
    UINT64 compilebufoffset,
    UINT64 databufid,
    UINT64 databufoffset,
    unsigned char* pname)
{
    UINT64 namelength = largestsignedint;

    const char* perror;

    // get length of name
    perror = dg_scanforbyte((void*)pname, &namelength, 0);

    if (perror != dg_success)
    {
        // ignoring errors for now, just not putting word in wordlist
        return(DG_ENDOFWORDLIST);
    }

    return(
        dg_newword(
            pBHarrayhead,
            compilebufid,
            compilebufoffset,
            databufid,
            databufoffset,
            DG_CORE_BUFFERID,
            (UINT64)pname,
            namelength)
    );
}


const char* dg_getpdefinitionname = "dg_getpdefinition";

Definitionheader* dg_getpdefinition (
    Bufferhandle* pBHarrayhead,
    UINT64 definitionid)
{
    Definitionheader* pdefinition;
    UINT64 valuelength;
                                 
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return((Definitionheader*)badbufferhandle);
    }
    
    pdefinition = (Definitionheader*)dg_getshlistelementvalue (
        pBHarrayhead,
        0, // hlistheaderid, hlist 0 reserved for wordlists
        definitionid, // elementid,
        &valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getpdefinitionname);
        return ((Definitionheader*)badbufferhandle);
    }
    
    //if (valuelength < sizeof(Definitionheader))
    //{
    //    dg_pusherror(pBHarrayhead, dg_getpdefinitionname);
   //     return ((Definitionheader*)badbufferhandle);
   // }
    
    return (pdefinition);
}


// converting to use hlists:
//  wordlist ids are now also element ids... so any word can essentially be a wordlist parent
const char* dg_linkdefinitionname = "dg_linkdefinition";

void dg_linkdefinition (
    Bufferhandle* pBHarrayhead,
    UINT64 vocabularyid,
    UINT64 definitionid)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_changehlistelementparent (
        pBHarrayhead,
        0, // hlistid, hlist 0 reserved for wordlist
        definitionid,
        vocabularyid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_linkdefinitionname);
    }
}


// converting to use hlists:
//  this is the same except won't need link definition
const char* dg_createovariablebufdefname = "dg_createovariablebufdef";

// could change this routine to accept name's offset bufferid instead
UINT64 dg_createovariablebufdef (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 databufid;
    UINT64 databufoffset;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypedpushdn;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    databufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createovariablebufdefname);
        return (definition);
    }

    // supposed to align here... 

    databufoffset = dg_getbufferlength(
        pBHarrayhead,
        databufid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createovariablebufdefname);
        return (definition);
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createovariablebufdefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset,
        DG_CORE_BUFFERID,
        (UINT64)pname, 
        namelength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createovariablebufdefname);
        return (definition);
    }

    dg_linkdefinition(pBHarrayhead, vocabid, definition);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_createovariablebufdefname);
        return (DG_ENDOFWORDLIST);
    }

    return(definition);
}



// converting to use hlists:
//  should be the same except link definition
const char* dg_createocompilebufdefname = "dg_createocompilebufdef";

// could change this routine to accept name's offset bufferid instead
UINT64 dg_createocompilebufdef (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 databufid;
    UINT64 databufoffset;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypedpushdn;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    databufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createocompilebufdefname);
        return (definition);
    }

    // supposed to align here... 

    databufoffset = dg_getbufferlength(
        pBHarrayhead,
        databufid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createocompilebufdefname);
        return (definition);
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createocompilebufdefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset, 
        DG_CORE_BUFFERID, 
        (UINT64)pname, 
        namelength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createocompilebufdefname);
        return (definition);
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_createocompilebufdefname);
        return (DG_ENDOFWORDLIST);
    }

    return(definition);
}


const char* dg_createsubthreaddefname = "dg_createsubthreaddef";

UINT64 dg_createsubthreaddef (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 databufid;
    UINT64 databufoffset;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypesubroutine;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    databufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createsubthreaddefname);
        return (definition);
    }

    databufoffset = dg_getbufferlength(
        pBHarrayhead,
        databufid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createsubthreaddefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset, 
        DG_CORE_BUFFERID,
        (UINT64)pname, 
        namelength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createsubthreaddefname);
        return (definition);
    }

    return(definition);
}


const char* dg_createvariabledefname = "dg_createvariabledef";

UINT64 dg_createvariabledef (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 databufid;
    UINT64 databufoffset;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypedpushp;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    databufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createvariabledefname);
        return (definition);
    }

    // supposed to align here... 

    databufoffset = dg_getbufferlength(
        pBHarrayhead,
        databufid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createvariabledefname);
        return (definition);
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createvariabledefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset, 
        DG_CORE_BUFFERID,
        (UINT64)pname, 
        namelength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createvariabledefname);
        return (definition);
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_createvariabledefname);
        return (DG_ENDOFWORDLIST);
    }

    return(definition);
}


const char* dg_createdconstantdefname = "dg_createdconstantdef";

UINT64 dg_createdconstantdef (
    Bufferhandle* pBHarrayhead,
    UINT64 databufoffset,
    UINT64 databufid,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypedpushdn;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createdconstantdefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset, 
        DG_CORE_BUFFERID,
        (UINT64)pname, 
        namelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createdconstantdefname);
        return (definition);
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_createdconstantdefname);
        return (DG_ENDOFWORDLIST);
    }

    return(definition);
}


const char* dg_createconstantdefname = "dg_createconstantdef";

UINT64 dg_createconstantdef (
    Bufferhandle* pBHarrayhead,
    UINT64 dataid,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 databufid = 0;
    UINT64 databufoffset = dataid;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypedpushn;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createconstantdefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset, 
        DG_CORE_BUFFERID,
        (UINT64)pname, 
        namelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createconstantdefname);
        return (definition);
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_createconstantdefname);
        return (DG_ENDOFWORDLIST);
    }

    return(definition);
}


const char* dg_createfconstantdefname = "dg_createfconstantdef";

UINT64 dg_createfconstantdef (
    Bufferhandle* pBHarrayhead,
    UINT64 dataid,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 databufid = 0;
    UINT64 databufoffset = dataid;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypedpushf;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createfconstantdefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset, 
        DG_CORE_BUFFERID,
        (UINT64)pname, 
        namelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createfconstantdefname);
        return (definition);
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_createfconstantdefname);
        return (DG_ENDOFWORDLIST);
    }

    return(definition);
}


const char* dg_getlatestdefinitionname = "dg_getlatestdefinition";

UINT64 dg_getlatestdefinition (
    Bufferhandle* pBHarrayhead,
    UINT64 vocabularyid)
{
    UINT64 definition = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (DG_ENDOFWORDLIST);
    }

    definition = dg_gethlistlastchildofparent (
        pBHarrayhead,
        0, // hlistheaderid, 0 reserved for wordlists
        vocabularyid); // parentelementid)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getlatestdefinitionname);
        return (DG_ENDOFWORDLIST);
    }
    
    return (definition);
}


const char* dg_getnextdefinitionname = "dg_getnextdefinition";

UINT64 dg_getnextdefinition (
    Bufferhandle* pBHarrayhead,
    UINT64 currentdefinition)
{
    UINT64 definition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (DG_ENDOFWORDLIST);
    }

    definition = dg_gethlistprevioussibling (
        pBHarrayhead,
        0, // hlistheaderid,
        currentdefinition); // childelementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getnextdefinitionname);
        return (DG_ENDOFWORDLIST);
    }
    
    return (definition);
}


const char* dg_executedefinitionname = "dg_executedefinition";

void dg_executedefinition (
    Bufferhandle* pBHarrayhead,
    UINT64 definitionid)
{
    Definitionheader* pdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    if (DG_ENDOFWORDLIST == definitionid)
    {
        return;
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definitionid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_executedefinitionname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->dataoffset);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_executedefinitionname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        pdefinition->databuf);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_executedefinitionname);
        return;
    }

    dg_callbuffer(
        pBHarrayhead, // do a safe call?
        pdefinition->compileroutinebuf, 
        pdefinition->compileroutineoffset);

    // can't report errors from this call
}


const char* dg_finddefinwordlistname = "dg_finddefinwordlist";

UINT64 dg_finddefinwordlist (
    Bufferhandle* pBHarrayhead,
    UINT64 vocabularyid,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 definition = 0;

//    unsigned char* pdefname = (unsigned char*)badbufferhandle;

    INT64 compareflag;
    
    UINT64 indexofkeyaftermatch;


    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (DG_ENDOFWORDLIST);
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_emptystringerror);
        dg_pusherror(pBHarrayhead, dg_finddefinwordlistname);
        return (DG_ENDOFWORDLIST);
    }
    
    compareflag = dg_findsortedhlistchild (
        pBHarrayhead,
        //(unsigned char*)"word", // ptag,
        //4, // taglength,
        pname,
        namelength,
        //0, // key,
        //FORTH_TRUE, // fmatchname, // if this flag is true, match the element's name attribute too
        //FORTH_TRUE, // fmatchkey, // if this flag is true, match the element's key attribute too
  
        0, // hlistheaderid, hlist 0 reserved for wordlists 
        vocabularyid, // parentelementid,
      
        &indexofkeyaftermatch, // index in sort key lstring after match
        &definition); // foundkey);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_finddefinwordlistname);
        return (DG_ENDOFWORDLIST);
    }
    
    if (0 != compareflag)
    {
        definition = DG_ENDOFWORDLIST;
    }
        
    return (definition);
}

UINT64 dg_getfinddefinsearchordermetrics(
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength,
    UINT64 numberofmicroseconds)
{
    UINT64 numberoftries = 0;
    UINT64 starttime = 0;
    UINT64 endtime = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(DG_ENDOFWORDLIST);
    }
    
    starttime = dg_getmicrosecondssince1970Jan01();
    
    // wait for a rollover - assumes preemptive or hardware clock
    while (dg_getmicrosecondssince1970Jan01() == starttime)
    {
    }
    
    endtime = starttime + numberofmicroseconds + 1;
    
    while (dg_getmicrosecondssince1970Jan01() < endtime)
    {
        dg_finddefinsearchorder (
            pBHarrayhead,
            pname,
            namelength);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, (const char*)"got error doing find during dg_getfinddefinsearchordermetrics");
            return(numberoftries);
        }
            
        numberoftries++;
    }
    
    return(numberoftries);
}

const char* dg_finddefinsearchordername = "dg_finddefinsearchorder";

UINT64 dg_finddefinsearchorder (
    Bufferhandle* pBHarrayhead,
    unsigned char* pname,
    UINT64 namelength)
{
    unsigned char* pso;
    UINT64* psolength;

    UINT64 i;
    UINT64 numtosearch;

    UINT64 vocabtosearch;
    UINT64 definition;
    
    UINT64 haslocalsflag;
    UINT64 haslocalstringsflag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(DG_ENDOFWORDLIST);
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_emptystringerror);
        dg_pusherror(pBHarrayhead, dg_finddefinsearchordername);
        return(DG_ENDOFWORDLIST);
    }
/*
    // check locals wordlist first
    haslocalsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalsflag);
        
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_finddefinsearchordername);
        return(DG_ENDOFWORDLIST);
    }
    
    haslocalstringsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalstringsflag);
        
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_finddefinsearchordername);
        return(DG_ENDOFWORDLIST);
    }
    
    if ((haslocalsflag != FORTH_FALSE) || (haslocalstringsflag != FORTH_FALSE))
    {
    */
    
        vocabtosearch = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_localswordlistid);
            
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_finddefinsearchordername);
            return(DG_ENDOFWORDLIST);
        }

        definition  = dg_finddefinwordlist(pBHarrayhead, vocabtosearch, pname, namelength);
        
        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_finddefinsearchordername);
            return(DG_ENDOFWORDLIST);
        }
        
        if (definition != DG_ENDOFWORDLIST)
        {
            return(definition);
        }
        
        /*
    }
    */
        

    pso = dg_getpbuffer(pBHarrayhead, DG_SEARCHORDERSTACK_BUFFERID, &psolength);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_finddefinsearchordername);
        return(DG_ENDOFWORDLIST);
    }

    if (*psolength < sizeof(UINT64))
    {
        // nothing to search!!!
        return(DG_ENDOFWORDLIST);
        //note! the standard specifies a way for the user to eliminate the search order, so this is ok
    }

    numtosearch = (*psolength) / sizeof(UINT64); // there should be no remainder from this divide and we should check it

    // start at end of search order stack and work your way back
    for (i = 0; i < numtosearch; i++)
    {
        vocabtosearch = ((UINT64*)pso)[numtosearch - (i+1)];

        definition  = dg_finddefinwordlist(pBHarrayhead, vocabtosearch, pname, namelength);

        if (pBHarrayhead->errorcount != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_finddefinsearchordername);
            // not going to return so we can at least search the core words

            // so next time through this loop only a new error will be caught
            olderrorcount = pBHarrayhead->errorcount;
        }

        if (definition != DG_ENDOFWORDLIST)
        {
            //found!
            break;
        }
    }

    return (definition);
}


const char* dg_changelatestcompileroutinename = "dg_changelatestcompileroutine";

void dg_changelatestcompileroutine (
    Bufferhandle* pBHarrayhead,
    UINT64 compilebufid,
    UINT64 compilebufoffset)
{
    Definitionheader* pdefinition;
    
    UINT64 mylatestdefinition;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    mylatestdefinition = dg_getbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_latestnewword);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_changelatestcompileroutinename);
        return;
    }
    
    if (DG_ENDOFWORDLIST == mylatestdefinition)
    {
        // there is no latest definition
        dg_pusherror(pBHarrayhead, dg_outsideofbuffererror);
        dg_pusherror(pBHarrayhead, dg_changelatestcompileroutinename);
        return;
    }
    
    pdefinition = dg_getpdefinition (
        pBHarrayhead,
        mylatestdefinition);
        
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_changelatestcompileroutinename);
        return;
    }

    pdefinition->compileroutinebuf = compilebufid;
    pdefinition->compileroutineoffset = compilebufoffset;
}


// this should also make the wordlist... which would make it a little faster too
const char* dg_newpresortedwordlistname = "dg_newpresortedwordlist";

UINT64 dg_newpresortedwordlist (
    Bufferhandle* pBHarrayhead,
    struct Premadeword *pmypresortedwordlist,
    UINT64 mypresortedwordlistlength)
{
    Hlistheader myhlistheader;
    UINT64 i;
    UINT64 previouselementid, nextelementid;
    
    UINT64 firstelementid = DG_ENDOFLIST;
    
    Freeablelstringarrayheader myelementheaderflstrah;
    Hlistelementheader* pparentelementheader = (Hlistelementheader*)(badbufferhandle);
    UINT64 parentelementheaderlength = 0;
    
    UINT64 wordlistid;
    UINT64 realnamelength;
    
    unsigned char* psortedkeyslstring;
    UINT64 sortedkeyslstringlength;
    
    const char* pError;
    
    Definitionheader mydefinitionheader;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return (DG_ENDOFLIST);
    }
    
    if (0 == mypresortedwordlistlength)
    {
        return (DG_ENDOFLIST);
    }
    
    wordlistid = dg_newwordlist(pBHarrayhead, 0);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
        return (DG_ENDOFLIST);
    }
    
    // get header
    dg_gethlistheader(
        pBHarrayhead,
        0, // hlistheaderid,
        &myhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
        return (DG_ENDOFLIST);
    }
    
    firstelementid = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        myhlistheader.namelstroffsetbufid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
        return (DG_ENDOFLIST);
    }
    
    for (i = 0; i < mypresortedwordlistlength; i++)
    {
        mydefinitionheader.compileroutinebuf    = pmypresortedwordlist[i].compileroutinebuf;
        mydefinitionheader.compileroutineoffset = pmypresortedwordlist[i].compileroutineoffset;
        mydefinitionheader.databuf              = pmypresortedwordlist[i].databuf;
        mydefinitionheader.dataoffset           = pmypresortedwordlist[i].dataoffset;
        
        if (0 == i)
        {
            previouselementid = DG_ENDOFLIST;
        }
        else
        {
            previouselementid = firstelementid + (i - 1);
        }
        
        if (i == (mypresortedwordlistlength - 1))
        {
            nextelementid = DG_ENDOFLIST;
        }
        else
        {
            nextelementid = firstelementid + i + 1;
        }

        realnamelength = (UINT64)largestsignedint;
        
        pError = dg_scanforbyte (
            (void*)(pmypresortedwordlist[i].pname), 
            &realnamelength, 
            0);
            
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_scanforbytename);
            dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
            return (DG_ENDOFLIST);
        }
        
        // push all elements
        dg_newunsortedhlistelement (
            pBHarrayhead,
            0, // hlistid,
            myhlistheader,
            wordlistid, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
            //0, // key,
            (unsigned char*)(pmypresortedwordlist[i].pname),
            //pmypresortedwordlist[i].namelength,
            realnamelength,
            //(unsigned char*)"word", // ptag
            //4, // taglength,
            (unsigned char*)&mydefinitionheader,
            sizeof(Definitionheader),
            previouselementid,
            nextelementid);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
            return (DG_ENDOFLIST);
        }
    }
    
    // make room in sorted keys and get s sorted keys - assumes it is emtpy
    dg_insertinlstring (
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        wordlistid, // parentelementid,
        0, // in bytes
        mypresortedwordlistlength * sizeof(UINT64));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
        return (DG_ENDOFLIST);
    }
    
    psortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myhlistheader.sortedchildidslstroffsetbufid,
        myhlistheader.sortedchildidslstrstringbufid,
        wordlistid, 
        &sortedkeyslstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
        return (DG_ENDOFLIST);
    }
    
    // add the keys
    for (i = 0; i < mypresortedwordlistlength; i++)
    {
        ((UINT64*)psortedkeyslstring)[i] = firstelementid + i;
    }
    
    // get hlist element header freeable lstring header
   dg_copyflstrheadertos(
        pBHarrayhead,
        myhlistheader.elementheaderflstrbufid,
        &myelementheaderflstrah,
        sizeof(Freeablelstringarrayheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
        return (DG_ENDOFLIST);
    }
    
    // get pointer to parent element header
    pparentelementheader = (Hlistelementheader*)dg_getplstring(
        pBHarrayhead,
        myelementheaderflstrah.lstringoffsetbufferid,
        myelementheaderflstrah.lstringstringbufferid,
        wordlistid, // parentelementheaderid,
        &parentelementheaderlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_newpresortedwordlistname);
        return (DG_ENDOFLIST);
    }
    
    pparentelementheader->lastchildelementid = firstelementid + (mypresortedwordlistlength - 1);
    
    return (wordlistid);
}

/*
DGLU_API unsigned char* dg_getslatestnewwordnom (Bufferhandle* pBHarrayhead)
{
    UINT64 latestnewword;
    unsigned char* pname;
    UINT64 namelength;
    
    latestnewword = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_latestnewword);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_getslatestnewwordnomname);
        return((unsigned char*)largestunsignedint);
    }
    
    if (latestnewword == DG_ENDOFWORDLIST)
    {
        return ((unsigned char*)largestunsignedint);
    }
    
    pname = dg_getshlistelementnom (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementid,
        UINT64* &namelength);
}
*/

const char dg_copyandrenamewordidname[] = "dg_copyandrenamewordid";

UINT64 dg_copyandrenamewordid (
    Bufferhandle* pBHarrayhead,
    UINT64 definitionid,
    unsigned char* pname,
    UINT64 namelength)
{
    Definitionheader* pdefinition;
    UINT64 newwordid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(DG_ENDOFWORDLIST);
    }
    
    if (DG_ENDOFWORDLIST == definitionid)
    {
        return(DG_ENDOFWORDLIST);
    }

    pdefinition = dg_getpdefinition(
        pBHarrayhead,
        definitionid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copyandrenamewordidname);
        return(DG_ENDOFWORDLIST);
    }
    
    newwordid = dg_newword (
        pBHarrayhead,
        pdefinition->compileroutinebuf, 
        pdefinition->compileroutineoffset,
        pdefinition->databuf,
        pdefinition->dataoffset,
        DG_CORE_BUFFERID,
        (UINT64)pname,
        namelength);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_copyandrenamewordidname);
        return(newwordid);
    }
    
    return (newwordid);
}

const char dg_findcopyandrenamewordname[] = "dg_findcopyandrenameword";

UINT64 dg_findcopyandrenameword (
    Bufferhandle* pBHarrayhead,
    unsigned char* poldname,
    UINT64 oldnamelength,
    unsigned char* pnewname,
    UINT64 newnamelength)
{
    UINT64 oldwordid;
    UINT64 newwordid;
    UINT64 base;
    UINT64 number;
    UINT64 flag;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return(DG_ENDOFWORDLIST);
    }
    
    oldwordid = dg_finddefinsearchorder (
        pBHarrayhead,
        poldname,
        oldnamelength);
        
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_findcopyandrenamewordname);
        return(DG_ENDOFWORDLIST);
    }
    
    if (DG_ENDOFWORDLIST == oldwordid)
    {        
        // try number, and try floating point number
        dg_pusherror(pBHarrayhead, dg_wordnotfoundinsearchordererror);
        dg_pusherror(pBHarrayhead, dg_findcopyandrenamewordname);
        return(DG_ENDOFWORDLIST);
    }
    
    newwordid = dg_copyandrenamewordid (
        pBHarrayhead,
        oldwordid,
        pnewname,
        newnamelength);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_findcopyandrenamewordname);
        return(newwordid);
    }
    
    return (newwordid);
}

const char dg_emptywordlistname[] = "dg_emptywordlist";

void dg_emptywordlist (
    Bufferhandle* pBHarrayhead,
    UINT64 parentelementid)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    dg_prunehlistelement (
        pBHarrayhead,
        DG_WORDLISTS_HLISTID,
        parentelementid);
    
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_emptywordlistname);
        return;
    }
}

const char* dg_createbrackettoorderconstantdefname = "dg_createbrackettoorderconstantdef";

UINT64 dg_createbrackettoorderconstantdef (
    Bufferhandle* pBHarrayhead,
    UINT64 wordlistid,
    unsigned char* pname,
    UINT64 namelength)
{
    UINT64 databufid = 0;
    UINT64 databufoffset = wordlistid;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypebrackettoorder;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return (definition);
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createbrackettoorderconstantdefname);
        return (definition);
    }

    definition = dg_newwordcopyname(
        pBHarrayhead, 
        compilebufid, 
        compilebufoffset, 
        databufid, 
        databufoffset, 
        DG_CORE_BUFFERID,
        (UINT64)pname, 
        namelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_createbrackettoorderconstantdefname);
        return (definition);
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_createbrackettoorderconstantdefname);
        return (DG_ENDOFWORDLIST);
    }

    return(definition);
}


