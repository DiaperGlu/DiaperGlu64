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

/*
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
*/

// note: pBHarrayhead pointer is no longer valid after call to dg_cleanup
//  ignoring errors in this routine because script is attempting to exit
void dg_cleanup (Bufferhandle* pBHarrayhead)
{
    UINT64 bufferlength = 0;
    UINT64 executiontoken = 0;
    UINT64 dllhandle = 0;
    const char* perror;

    UINT64 desiredsize = sizeof(Bufferhandle) + jumpbufferlength;
    UINT64 pagesize = dg_getpagesize();
    UINT64 truesize;

    truesize = ((UINT64)((desiredsize-1) / pagesize) + 1) * pagesize;

    bufferlength = dg_getbufferlength(
        pBHarrayhead,
        DG_CLEANUP_BUFFERID);

    while (bufferlength >= sizeof(UINT64))
    {
        executiontoken = dg_popbufferuint64(
            pBHarrayhead,
            DG_CLEANUP_BUFFERID);

        dg_executedefinition(
            pBHarrayhead,
            executiontoken);

        // don't care about errors because we are exiting

        bufferlength = dg_getbufferlength(
            pBHarrayhead,
            DG_CLEANUP_BUFFERID);
    }

    bufferlength = dg_getbufferlength(
        pBHarrayhead,
        DG_LIBHANDLE_BUFFERID);

    while (bufferlength >= sizeof(UINT64))
    {
        dllhandle = dg_popbufferuint64(
            pBHarrayhead,
            DG_LIBHANDLE_BUFFERID);

        perror = dg_freelibrary(
            dllhandle,
            dg_success);

        // don't care about errors because we are exiting

        bufferlength = dg_getbufferlength(
            pBHarrayhead,
            DG_LIBHANDLE_BUFFERID);
    }

    dg_freeallbuffers(pBHarrayhead);

    dg_free(
        pBHarrayhead,
        truesize,
        dg_success);
}
/*
UINT64 dg_gettruesize()
{
    UINT64 desiredsize = sizeof(Bufferhandle) + jumpbufferlength;
    UINT64 pagesize = dg_getpagesize();
    UINT64 truesize = ((UINT64)((desiredsize-1) / pagesize) + 1) * pagesize;
    
    return (truesize);
}
*/

Bufferhandle* dg_initwithoutwordlists(int argc, char* argv[])
{
    Bufferhandle* pBHarrayhead = (Bufferhandle*)badbufferhandle;
    // void* pjumpbuffer;
    const char* flag;

    // needed for freebsd 6 statically linked executable
    //dg_initenvironment (argc, argv);
    
    const char* pError;
    
    // for linux compatibility
    UINT64 truesize = dg_gettruesize();

    // allocating pBHarrayhead and jumpbuffer in one buffer
    // in Linux dg_malloc fails unless size is multiple of page size
    // since jump buffer goes in here, memory returned must be executable
    flag = dg_malloc(
        (void**)&pBHarrayhead,
        truesize,
        dg_success);

    if (flag != dg_success)
    {
        return ((Bufferhandle*)badbufferhandle); // for Linux memory allocation, 0 is valid return 
    }
    
    pBHarrayhead->argc = argc;
    pBHarrayhead->argv = argv;
 
    // pjumpbuffer = (char*)((unsigned char*)pBHarrayhead + sizeof(Bufferhandle));
    
    dg_initpbharrayhead(pBHarrayhead);
    
    // checking for bad memory in arguments list and environment variables
      // windows environment variables done differently
      // in isapi, skip this altogether
    // pError = dg_checkargs(argc, argv);
    
    // if (pError != dg_success)
    // {
    //    dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error checking arguments list and environment variables passed in to Diaperglu\n");
    //    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  got ");
    //    dg_printzerostring(pBHarrayhead, (unsigned char*)pError);
    //    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    //    dg_freeallbuffers(pBHarrayhead);
    //    dg_free((void*)pBHarrayhead, truesize, dg_success);
    //    return((Bufferhandle*)badbufferhandle);
    // }
    
    pError = dg_initbuffers(pBHarrayhead);
    
    if (pError != dg_success)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error initializing buffers\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  got ");
        dg_printzerostring(pBHarrayhead, (unsigned char*)pError);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, truesize, dg_success);
        return((Bufferhandle*)badbufferhandle);
    }

    dg_initvariables(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error initializing variables\n");
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  got ");
        dg_printzerostring(pBHarrayhead, (unsigned char*)pError);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, truesize, dg_success);
        return((Bufferhandle*)badbufferhandle);
    }
    
    dg_inithlists (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error initializing wordlist hlist\n");
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, truesize, dg_success);
        return((Bufferhandle*)badbufferhandle);
    }

    dg_forthleftbracket(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error setting state to execute\n");
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, truesize, dg_success);
        return((Bufferhandle*)badbufferhandle);
    }

    dg_initjumpbuffer(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error initializing jumpbuffer\n");
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, truesize, dg_success);
        return((Bufferhandle*)badbufferhandle);
    }

    dg_argstoargsbuffer(pBHarrayhead, argc, argv);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error copying args to args buffer\n");
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, truesize, dg_success);
        return((Bufferhandle*)badbufferhandle);
    }

/*
    dg_initwordlists(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error initializing wordlists\n");
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, truesize, dg_success);
        return((Bufferhandle*)badbufferhandle);
    }
*/
    return (pBHarrayhead);
}

Bufferhandle* dg_init(int argc, char* argv[])
{
    Bufferhandle* pBHarrayhead;
    
    pBHarrayhead = dg_initwithoutwordlists(argc, argv);
    
    dg_initwordlists(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != 0)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nGot an error initializing wordlists\n");
        dg_forthdoterrors(pBHarrayhead);
        dg_freeallbuffers(pBHarrayhead);
        dg_free((void*)pBHarrayhead, dg_gettruesize(), dg_success);
        return((Bufferhandle*)badbufferhandle);
    }
    
    return (pBHarrayhead);
}

void dg_donglu (int argc, char* argv[])
{
    Bufferhandle* pBHarrayhead;
    
    pBHarrayhead = dg_initwithoutwordlists(argc, argv);
    
    
}

void dg_main (int argc, char* argv[])
{
    Bufferhandle* pBHarrayhead;
    // UINT64 myrsp;

    pBHarrayhead = dg_init(argc, argv);
    
    // dg_forthshowbuffers(pBHarrayhead);

    if (pBHarrayhead != (Bufferhandle*)badbufferhandle)
    {
        if (0 == dg_geterrorcount(pBHarrayhead))
        {
            // myrsp = (UINT64)dg_getretstackpointer();

            // dg_printzerostring(pBHarrayhead, (unsigned char*)"Return stack pointer just before calling a subroutine = ");
            // dg_writestdoutuint64tohex(pBHarrayhead, myrsp);
            // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
            
            dg_forthquit(pBHarrayhead);
        }

        dg_cleanup(pBHarrayhead);
    }
}
/*
int main(int argc, char* argv[])
{
    dg_main(argc, argv);

    return(0);
}
*/

// Note Windows: added /opt:noref to general link settings to get rid of warning message 6/09/2004
