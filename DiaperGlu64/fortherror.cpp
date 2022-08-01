// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.6.
//
//    DiaperGlu v5.6 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.6 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.6; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// August 1, 2022             //
// version 5.6                //
// /////////////////////////////



#include "diapergluforth.h"


void dg_forthpushoerror (Bufferhandle* pBHarrayhead) 
//     ( offset bufferid -- )
//     ( -error- offset bufferid )
{
    UINT64 offset = 0;
    UINT64 bufferid = 0;

    bufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    offset = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    dg_pushbuffererror(
        pBHarrayhead,
        bufferid,
        offset);
}


void dg_forthpopoerror (Bufferhandle* pBHarrayhead)
//             ( offset bufferid -error- )
//             ( -- offset bufferid )
{
    UINT64 offset;
    UINT64 bufid;

    dg_popbuffererror(
        pBHarrayhead,
        &offset,
        &bufid);

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        offset);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        bufid);
}


void dg_forthgetoerror (Bufferhandle* pBHarrayhead) // GETOERROR0$
//     ( errorstackindex -- offset bufferid )
{
    UINT64 bufferid;
    UINT64 offset;
    UINT64 errorindex;

    errorindex = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    dg_getbuffererror(
        pBHarrayhead,
        errorindex,
        &offset,
        &bufferid);

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        offset);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        bufferid);
}


void dg_forthgeterrorcount (Bufferhandle* pBHarrayhead) // GETERRORCOUNT
//     ( -- errorcount )
{
    UINT64 errorcount = 0;

    errorcount = dg_geterrorcount(pBHarrayhead);

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        errorcount);
}


void dg_forthcheckerrordepth (Bufferhandle* pBHarrayhead) // GETERRORDEPTH
//     ( -- errorstackdepth )
{
    UINT64 errorstackdepth = dg_checkerrorsonstack(pBHarrayhead);

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        errorstackdepth);
}


void dg_forthcompilegetolderrorcount (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // could make something more direct...
    dg_compilepusholderrorcounttoret(pBHarrayhead);
    
    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthcplgetolderrorcountname);
    }
    
    dg_compilepushdatastack(pBHarrayhead);
    
    if (olderrorcount != dg_geterrorcount(pBHarrayhead))
    {
        dg_pusherror(pBHarrayhead, dg_forthcplgetolderrorcountname);
    }
}


void dg_forthdroptoerrorcount (Bufferhandle* pBHarrayhead)
{
    UINT64 newerrorcount = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);

    dg_droptoerrorcount(
        pBHarrayhead,
        newerrorcount);
}

/*
void dg_getserrormessage (
    Bufferhandle* pBHarrayhead,
    UINT64 errorbufferid,
    UINT64 erroroffset,
    unsigned char** pperror,
    UINT64* perrorlength)
{
    const char* flag = dg_success;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    flag = dg_putuint64(
        (UINT64*)pperror,
        (UINT64)badbufferhandle);

    if (flag != dg_success)
    {
        return;
    }
    
    flag = dg_putuint64(
        (UINT64*)perrorlength,
        0);

    if (flag != dg_success)
    {
        return;
    }
    
    if (DG_CORE_BUFFERID == errorbufferid)
    {
    
        *pperror = (unsigned char*)erroroffset;
        
        // setting maxlength
        *perrorlength = largestunsignedint;
    
        flag = dg_scanforbyte (
            (void*)erroroffset,
            perrorlength,
            0);
    
        if (flag != dg_success)
        {
            // could return a message indicating couldn't get length instead
            *perrorlength = 0;
        }
        
        return;
    }
    
    if (DG_WORDNAME_FAKE_BUFFERID == errorbufferid)
    {
        *pperror = dg_getshlistelementnom (
            pBHarrayhead,
            0, // hlistheaderid, // hlist 0 reserved for the wordlist
            erroroffset, // elementid,
            perrorlength);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_droptoerrorcount(pBHarrayhead, olderrorcount);
            
            // could set error to a message indicating couldn't get hlist element name
            *pperror = (unsigned char*)badbufferhandle;
            *perrorlength = 0;
        }
        
        return;
    }
    
    if (DG_WORDVALUE_FAKE_BUFFERID == errorbufferid)
    {
        *pperror = dg_getshlistelementvalue (
            pBHarrayhead,
            0, // hlistheaderid, // hlist 0 reserved for the wordlist
            erroroffset, // elementid,
            perrorlength);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_droptoerrorcount(pBHarrayhead, olderrorcount);
            
            // could set error to a message indicating couldn't get hlist element name
            *pperror = (unsigned char*)badbufferhandle;
            *perrorlength = 0;
        }
        
        return;
    }
    
    *pperror = dg_getpbufferoffset  (
        pBHarrayhead,
        errorbufferid,
        erroroffset);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_droptoerrorcount(pBHarrayhead, olderrorcount);
            
        // could set error to a message indicating couldn't get hlist element name
        *pperror = (unsigned char*)badbufferhandle;
        *perrorlength = 0;
    }
    
    // setting maxlength
    *perrorlength = largestunsignedint;
    
    flag = dg_scanforbyte (
        (void*)(*pperror),
        perrorlength,
        0);
    
    if (flag != dg_success)
    {
        // could return a message indicating couldn't get length instead
        *perrorlength = 0;
    }
}
*/
/*
void dg_forthdoterrors (Bufferhandle* pBHarrayhead)
{
    UINT64 errorcount;
    unsigned char* perror;
    UINT64 errorlength;
    UINT64 i;
    UINT64 errorbufferid;
    UINT64 erroroffset;

    unsigned char c = '\n';
    unsigned char* punknownword;

    errorcount = dg_checkerrorsonstack(pBHarrayhead);

    if (errorcount == 0)
    {
        if (dg_geterrorcount(pBHarrayhead) == 0)
        {
            dg_printzerostring(pBHarrayhead, (unsigned char*)"no errors\n");
        }
        else
        {
            dg_printzerostring(pBHarrayhead, (unsigned char*)"error count corrupt - no errors on error stack but error count is not 0\n");
        }

        return;
    }

    for (i = errorcount; i > 0; i--)
    {
        //error = dg_geterror(pBHarrayhead, i-1);
        
        dg_getbuffererror (
            pBHarrayhead, 
            i-1, //errorindex, 
            &erroroffset, 
            &errorbufferid);

        if (
            ((dg_evaluatebufferwordnotfounderror == (const char*)erroroffset) ||
            (dg_symbolnotfounderror == (const char*)erroroffset))
             && (DG_CORE_BUFFERID == errorbufferid))
        {
            punknownword = dg_getpbufferoffset(
                pBHarrayhead,
                DG_DATASPACE_BUFFERID,
                lastnotfoundword);
            
            //dg_getserrormessage (
            //    pBHarrayhead,
            //    errorbufferid,
            //    erroroffset,
            //    &perror,
            //    &errorlength);

            if (punknownword != NULL)
            {
                dg_printzerostring(
                    pBHarrayhead,
                    (unsigned char*)" - word/symbol not found error (showing last word/symbol not found) >>>");
                
                dg_printzerostring(
                    pBHarrayhead,
                    (unsigned char*)punknownword);
                
                dg_printzerostring(
                    pBHarrayhead,
                    (unsigned char*)"<<<\n");
                //dg_writestdout(pBHarrayhead, perror, errorlength);
            }
        }
        else
        {
            dg_getserrormessage (
                pBHarrayhead,
                errorbufferid,
                erroroffset,
                &perror,
                &errorlength);
    
            //dg_printzerostring(pBHarrayhead, (unsigned char*)error);
            dg_writestdout(
                pBHarrayhead,
                perror,
                errorlength);

            dg_writestdout(
                pBHarrayhead,
                &c,
                1);
        }

        // just in case
        //if (error == dg_errornotthatmanyerrors)
        if ((dg_errornotthatmanyerrors == (const char*)erroroffset) && (DG_CORE_BUFFERID == errorbufferid))
        {
            break;
        }
    }

    if (dg_geterrorcount(pBHarrayhead) > errorcount)
    {
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"\nerror stack overflowed\n");
    }

    if (dg_geterrorcount(pBHarrayhead) < errorcount)
    {
        dg_printzerostring(
            pBHarrayhead,
            (unsigned char*)"\nerror count was less than errors on stack, this shouldn't happen\n");
    }
}
*/

///////////////////////////////////////////////////
// if you are looking for a dg_forthclearerrors, //
// see dg_clearerrors in cerror.cpp              //
///////////////////////////////////////////////////

void dg_forthbracketwordnametoerror (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthbracketlatest(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketwordnametoerrorname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        (UINT64)DG_WORDNAME_FAKE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketwordnametoerrorname);
        return;
    }
    
    dg_forthliteral(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketwordnametoerrorname);
        return;
    }
    
    dg_compilecallcore (
        pBHarrayhead,
        (UINT64)&dg_forthpushoerror);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbracketwordnametoerrorname);
        return;
    }
}


void dg_forthnametoe (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthbracketwordnametoerror(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnametoename);
        return;
    }
}


void dg_fortherrorquotes( Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_fortho0quotes(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fortherrorquotesname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)(&dg_forthpushoerror));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_fortherrorquotesname);
        return;
    }

    dg_forthcompilecallcore(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_fortherrorquotesname);
        return;
    }
}


void dg_forthqueryerrorif (Bufferhandle* pBHarrayhead)
//     ( -- ifoffset )
{
    UINT64 afterbranchoffset;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_compilequeryerror (pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryerrorifname);
        return;
    }

    afterbranchoffset = dg_compilebranch(
        pBHarrayhead,
        DG_BRANCHTYPE_EQUAL);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryerrorifname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        afterbranchoffset);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthqueryerrorifname);
        return;
    }
}
