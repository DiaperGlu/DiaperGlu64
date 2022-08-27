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

// dg_forthparenlocal ( addr u -- )
//  if u > 0, create constant with name addr u and value = current local index, increase current local index
//  if u = 0, compile code that allocates current local index number of locals
//  compile type of the locals is fetchlocal... which compiles code that does push [rbp+n] to data stack

// dg_forthto
//   parse next word, if it's compile type local, compile code that pops number off data stack to [rbp+n]

// {: before before -- does parenlocal for each name found ... and counts the number of locals before | 
//     after -- just looks for :}
//     when it's done it does parenlocal with no namelength then compiles code that does mov n things from
//      data stack to the correct local variables... for speed do a block copy (get pointer to data stack..
//      move n...  probably faster to compile separate moves for each one since.... MOVS has startup cost..

/*
const char* dg_savelocalstackdepthname = "dg_savelocalstackdepth";

void dg_savelocalstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 localbufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // get depth of local stack
    localbufferlength = dg_getbufferlength(
        pBHarrayhead, 
        DG_LOCALS_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocalstackdepthname);
        return;
    }
    
    if ((localbufferlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederrorname);
        dg_pusherror(pBHarrayhead, dg_savelocalstackdepthname);
    }
    
    // save it to the depth stack
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_LOCALS_STACKDEPTH_BUFFERID,
        localbufferlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocalstackdepthname);
        return;
    }
        
    return;
}

const char* dg_restorelocalstackdepthname = "dg_restorelocalstackdepth";

void dg_restorelocalstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 oldlocalbufferlength;
    
    unsigned char* plocalstack;
    UINT64* plocalsstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    oldlocalbufferlength = dg_popbufferuint64(
        pBHarrayhead, 
        DG_LOCALS_STACKDEPTH_BUFFERID);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
        return;
    }
    
    plocalstack = dg_getpbuffer(
        pBHarrayhead, 
        DG_LOCALS_DATASTACK_BUFFERID, 
        &plocalsstacklength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
        return;
    }
    
    if ((oldlocalbufferlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederrorname);
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
    }
    
    if (*plocalsstacklength < oldlocalbufferlength)
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_restorelocalstackdepthname);
        return;
    }
    
    *plocalsstacklength = oldlocalbufferlength;
}
*/

const char* dg_forthlocalsfetchname = "LOCALS@";

void dg_forthlocalsfetch (Bufferhandle* pBHarrayhead)
// ( localsindex -- u )
{
    UINT64 localsindex;
    UINT64 localsoffset;
    UINT64 localsvalue;
    
    UINT64 oldlocalsstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    
    localsindex = dg_popdatastack(pBHarrayhead);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsfetchname);
        return;
    }
    
    // get top value from locals depth stack
      // doing it the slow way right now
    oldlocalsstackdepth = dg_popbufferuint64(
        pBHarrayhead,
        DG_LOCALS_STACKDEPTH_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsfetchname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LOCALS_STACKDEPTH_BUFFERID,
        oldlocalsstackdepth);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsfetchname);
        return;
    }
    
    // need to check for overflow
    if (localsindex > (largestunsignedint >> 3))
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_forthlocalsfetchname);
        return;
        
    }
    
    if ((localsindex << 3) > (largestunsignedint - oldlocalsstackdepth))
    {
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_forthlocalsfetchname);
        return;
    }
    
    localsoffset = oldlocalsstackdepth + (localsindex << 3);
    
    localsvalue = dg_getbufferuint64(
        pBHarrayhead,
        DG_LOCALS_DATASTACK_BUFFERID,
        localsoffset);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsfetchname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        localsvalue);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsfetchname);
        return;
    }
}

const char* dg_forthlocalsstorename = "LOCALS!";

void dg_forthlocalsstore(Bufferhandle* pBHarrayhead)
// ( u localsindex -- )
{
    UINT64 localsindex;
    UINT64 localsoffset;
    UINT64 localsvalue;
    
    UINT64 oldlocalsstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    
    localsindex = dg_popdatastack(pBHarrayhead);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
    
    localsvalue = dg_popdatastack(pBHarrayhead);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
    
    // get top value from locals depth stack
      // doing it the slow way right now
    oldlocalsstackdepth = dg_popbufferuint64(
        pBHarrayhead,
        DG_LOCALS_STACKDEPTH_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LOCALS_STACKDEPTH_BUFFERID,
        oldlocalsstackdepth);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
    
    // need to check for overflow
    if (localsindex > (largestunsignedint >> 3))
    {
        dg_pusherror(pBHarrayhead, dg_erroroverflow);
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
        
    }
    
    if ((localsindex << 3) > (largestunsignedint - oldlocalsstackdepth))
    {
        dg_pusherror(pBHarrayhead, dg_erroroverflow);
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
    
    localsoffset = oldlocalsstackdepth + (localsindex << 3);
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_LOCALS_DATASTACK_BUFFERID,
        localsoffset,
        localsvalue);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
}


const char* dg_forthtolocalsname = ">LOCALS";

void dg_forthtolocals(Bufferhandle* pBHarrayhead)
// ( u -- )
// ( -locals- u )
{
    UINT64 u;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    u = dg_popdatastack(pBHarrayhead);
     
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LOCALS_DATASTACK_BUFFERID,
        u);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsstorename);
        return;
    }
}


const char* dg_forthdocompiletypelocalname = "dg_forthdocompiletypelocal";

void dg_forthdocompiletypelocal (Bufferhandle* pBHarrayhead)
//                         ( dataoffset databufid -- )
{
    UINT64 n;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthdrop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocalname);
        return;
    }
    
    n = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocalname);
        return;
    }
    
    dg_compilepushntodatastack (
        pBHarrayhead,
        n);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocalname);
        return;
    }
    
    dg_compilecallcore (
        pBHarrayhead,
        (UINT64)(&dg_forthlocalsfetch));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocalname);
        return;
    }

    /*
    dg_forthliteral(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocalname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        (UINT64)(&dg_forthlocalsfetch));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocalname);
        return;
    }

    dg_forthcompilecallcore(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocalname);
        return;
    }
    */
}


const char* dg_forthdocompiletypetofastlocalname = "dg_forthdocompiletypetofastlocal";

void dg_forthdocompiletypetofastlocal (Bufferhandle* pBHarrayhead)
//                         ( dataoffset databufid -- )
{
    UINT64 n;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthdrop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypetofastlocalname);
        return;
    }
    
    n = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypetofastlocalname);
        return;
    }
    
    dg_compiledatastacktobracketrbpd (
        pBHarrayhead,
        n); // displacement) need to covert the local index to an rbp offset

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypetofastlocalname);
        return;
    }
}


const char* dg_forthdocompiletypefastlocalfromname = "dg_forthdocompiletypefastlocalfrom";

void dg_forthdocompiletypefastlocalfrom (Bufferhandle* pBHarrayhead)
//                         ( dataoffset databufid -- )
{
    UINT64 n;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\ndoing fast local\n");

    dg_forthdrop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypefastlocalfromname);
        return;
    }
    
    n = dg_popdatastack(pBHarrayhead); // should be displacement
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypefastlocalfromname);
        return;
    }
    
    dg_compilebracketrbpdtodatastack (
        pBHarrayhead,
        n); // displacement) need to covert the local index to an rbp offset

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypefastlocalfromname);
        return;
    }
}


const char* dg_forthbarname = "|";
const char* dg_localsbarmissingerror = "error - end of subroutine or buffer encountered before |. | has to have a space before next word";

void dg_forthlocalsbar(Bufferhandle* pBHarrayhead)
{
    const char* pError;

    // UINT64 forthbarnamelength = largestunsignedint;
    
    UINT64 wordlength;
    unsigned char* pword;
    UINT64 foundendflag = FORTH_FALSE;
    
    INT64 compareflag;
    
    UINT64 relativeindex = 0;
    
    UINT64 localwordid;
    
    UINT64 localswordlistid;
    
    UINT64 usinglocalsflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
		return;
    }

/*    
    pError = dg_scanforbyte(
        (unsigned char*)dg_forthbarname,
        &forthbarnamelength,
        0);

    if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
		return;
	}
 */   
    
    usinglocalsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
        return;
    }
        
    if (FORTH_FALSE == usinglocalsflag)
    {
        // compile call to save local stack depth
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)(&dg_savelocalstackdepth));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
            return;
        }

        dg_forthcompilecallcore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
            return;
        }

        // set using locals flag
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_colonhaslocalsflag,
            FORTH_TRUE);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
            return;
        }
        
        relativeindex = 0;
    }
    else
    {
        relativeindex = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_numberoflocals);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
            return;
        }
    }
        
    // parse words until you get | as the whole word - I'm gonna treat other words starting with | as not the end
    while(foundendflag == FORTH_FALSE)
    {
        pword = dg_parsewords(
            pBHarrayhead,
            &wordlength,
            (unsigned char)'|', // enddelimiter,
            &foundendflag,
            FORTH_FALSE);
            
        // dg_forthparseword (pBHarrayhead);
        // ( "<delimeters>word<delimeters>morestuff" -currentinputbuffer- "morestuff" )
        // ( -- addr length )
        
        // wordlength = dg_popdatastack(pBHarrayhead);
        
        // pword = (unsigned char*)dg_popdatastack(pBHarrayhead);
        
        // length = 0 is error
        // if (0 == wordlength)
        // {
        //    dg_pusherror(pBHarrayhead, dg_localsbarmissingerror);
        //    dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
        //    return;
        // }
        
        if (wordlength != 0)
        {
            // word = ; is error
            pError = dg_comparebytes(
                pword,
                wordlength,
                (unsigned char*)dg_forthsemicolonname,
                dg_forthsemicolonnamelength,
                &compareflag);
            
            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_comparebytesname);
                dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
                return;
            }
        
            if (0 == compareflag)
            {
                dg_pusherror(pBHarrayhead, dg_localsbarmissingerror);
                dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);  
                return;
            }
        
            // otherwise create a new word and compile call to pushn to locals
            // compile call to push n to local stack
            dg_pushbufferuint64(
                pBHarrayhead,
                DG_DATASTACK_BUFFERID,
                (UINT64)(&dg_forthtolocals));

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
                return;
            }

            dg_forthcompilecallcore(pBHarrayhead);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
                return;
            }
        
            localwordid = dg_newwordcopyname (
                pBHarrayhead,
                (UINT64)DG_CORE_BUFFERID,
                (UINT64)&dg_forthdocompiletypelocal,
                0, // databufid,
                relativeindex, // databufoffset,
                (UINT64)DG_CORE_BUFFERID,
                (UINT64)pword,
                wordlength);
    
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
                return;
            }
        
            dg_linkdefinition(
                pBHarrayhead,
                localswordlistid,
                localwordid);
        
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
                return;
            }
        
            relativeindex++;
        }
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberoflocals,
        relativeindex);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalsbarname);
        return;
    }
}

void dg_forthclearlocalwordlist (Bufferhandle* pBHarrayhead)
{
    UINT64 localswordlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthclearlocalwordlistname);
		return;
    }
    
    dg_prunehlistelement (
        pBHarrayhead,
        0, // hlistheaderid,
        localswordlistid); // elementheaderid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthclearlocalwordlistname);
        return;
    }
}

void dg_forthquerycompileunnestlocals (Bufferhandle* pBHarrayhead)
{
    UINT64 usinglocalsflag;
    UINT64 usinglocallstringsflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    usinglocalsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerycompileunnestlocalsname);
		return;
    }
    
    usinglocallstringsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalstringsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthquerycompileunnestlocalsname);
		return;
    }
    
    if (FORTH_FALSE != usinglocalsflag)
    {
        // also need to compile call to restore local stack depth
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)(&dg_restorelocalstackdepth));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthquerycompileunnestlocalsname);
            return;
        }
        
        dg_forthcompilecallcore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthquerycompileunnestlocalsname);
            return;
        }
    }
    
    if (FORTH_FALSE != usinglocallstringsflag)
    {
        // also need to compile call to restore local lstring stack depth
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)(&dg_restorelocallsstackdepth));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthquerycompileunnestlocalsname);
            return;
        }

        dg_forthcompilecallcore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthquerycompileunnestlocalsname);
            return;
        }
    }
}

// need word to empty locals wordlist and clear the using locals flag
// const char* dg_forthqueryclearlocalsname = "?CLEAR-LOCALS";

void dg_forthqueryclearlocals(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    /*
    // for the x86 assembler
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcparameters,
        0);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
    
    // for the x86 assembler
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberofcfparameters,
        0);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
    */
    
    // now clearing locals wordlist every time this function is called 8/9/2020
    //  this is so I can support local constants
    dg_forthclearlocalwordlist(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
    
    dg_forthquerycompileunnestlocals(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberoflocals,
        0);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
        
    // clear using locals flag
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalsflag,
        FORTH_FALSE);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberoflocalstrings,
        0);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
        
    // clear using local lstrings flag
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalstringsflag,
        FORTH_FALSE);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
}

/*
void dg_forthusinglocals(Bufferhandle* pBHarrayhead)
{
    UINT64 usinglocalsflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    usinglocalsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalsflag);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthusinglocalsname);
        return;
    }
    
    if (FORTH_FALSE == usinglocalsflag)
    {
        // compile call to save local stack depth
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)(&dg_savelocalstackdepth));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthusinglocalsname);
            return;
        }

        dg_forthcompilecallcore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthusinglocalsname);
            return;
        }

        // set using locals flag
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_colonhaslocalsflag,
            FORTH_TRUE);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthusinglocalsname);
            return;
        }
    }
}

void dg_forthlocalssynonym (Bufferhandle* pBHarrayhead)
{
    unsigned char* poldname;
    UINT64 oldnamelength;
    unsigned char* pnewname;
    UINT64 newnamelength;
    UINT64 newwordid;
    UINT64 localswordlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    poldname = dg_parseword(
        pBHarrayhead,
        &oldnamelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalssynonymname);
        return;
    }
        
    pnewname = dg_parseword(
        pBHarrayhead,
        &newnamelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalssynonymname);
        return;
    }
    
    // this needs to try a number too...
    newwordid = dg_findcopyandrenameword (
        pBHarrayhead,
        poldname,
        oldnamelength,
        pnewname,
        newnamelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalssynonymname);
        return;
    }
    
    if (newwordid == DG_ENDOFWORDLIST)
    {
        // not sure if this is the right error... but technically you shouldn't
        //  get DG_ENDOFWORDLIST unless there was an error...
        dg_pusherror(pBHarrayhead, dg_wordnotfoundinsearchordererror);
        dg_pusherror(pBHarrayhead, dg_forthlocalssynonymname);
        return;
    }
    
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalssynonymname);
        return;
    }
    
    dg_linkdefinition (
        pBHarrayhead,
        localswordlistid,
        newwordid);
        
    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalssynonymname);
        return;
    }
}
*/

// 3 states:
//  parsing uninitialized locals
//  parsing initialized locals... initialized from data stack in forward order
//  parsing a comment
//  } ends the parse...
//  | in first start switches parse to second state
//  -- in first or second state switches parse to third state

// relativeindex = 0
// start of initialized locals = -1 (not used)
// state = parsing uninitialized
// begin
//  parse word
//  case | found  remember relative index as start of initialized locals
//  case -- found  break  remember current relative index and -- was found
//  case end found  break  remember current relative index and end was found
//  case default
//   create new local locals fetch word with relative index
// done until
//
// if there are initialized locals
//   compile code to initialize initialized locals from data stack
//   (for each initialized local starting with highest one do pop data stack and store local)
//
// if -- was found parse until } is found
// eat terminator
// end

const char* dg_forthendcurlybracename = "}";

void dg_forthcurlybrace (Bufferhandle* pBHarrayhead)
{
    const char* pError;
    
    UINT64 wordlength;
    unsigned char* pword;
    UINT64 foundendflag = FORTH_FALSE;
    
    INT64 compareflag;
    
    UINT64 localwordid;
    
    UINT64 localswordlistid;

    UINT64 startofinitializedlocals = largestunsignedint;

    UINT64 startreturnstackdepth;
    // UINT64 currentreturnstackdepth;
    UINT64 numberoflocals = 0;
    UINT64 i;
    UINT64 state = 0;

    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    startreturnstackdepth =
        dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_colonreturnstackdepth);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
        return;
    }

    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
        return;
    }
     
    while(foundendflag == FORTH_FALSE)
    {
        pword = dg_parsewords(
            pBHarrayhead,
            &wordlength,
            (unsigned char)'}', // enddelimiter,
            &foundendflag,
            FORTH_FALSE);
            
        if (wordlength != 0)
        {
            pError = dg_comparebytes(
                pword,
                wordlength,
                (unsigned char*)"|",
                1,
                &compareflag);
            
            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_comparebytesname);
                dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
                return;
            }
        
            if (0 == compareflag)
            {
                if (0 == state)
                {
                    startofinitializedlocals = numberoflocals; 
                    state = 1;
                }
                else
                {
                    // can only have one | error
                    dg_pusherror(pBHarrayhead, (const char*)"can only have one |");
                    dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
                    return;
                }
            }
            else
            {
                pError = dg_comparebytes(
                    pword,
                    wordlength,
                   (unsigned char*)"--",
                    2,
                    &compareflag);
            
                if (pError != dg_success)
                {
                    dg_pusherror(pBHarrayhead, pError);
                    dg_pusherror(pBHarrayhead, dg_comparebytesname);
                    dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
                    return;
                }

                if (0 == compareflag)
                {
                    state = 2;
                }
                else
                {
                    // otherwise create a new word 
                    if ((0 == state) || (1 == state))
                    {
                        // not checking for overflow since you'd need almost 2^64 for that to happen...
                        //  but if I did... just check for 0?

                        localwordid = dg_newwordcopyname (
                            pBHarrayhead,
                            (UINT64)DG_CORE_BUFFERID,
                            (UINT64)&dg_forthdocompiletypefastlocalfrom,
                            0, // databufid,
                            0 - ((numberoflocals + startreturnstackdepth + 1) << 3), // databufoffset,
                            (UINT64)DG_CORE_BUFFERID,
                            (UINT64)pword,
                            wordlength);
    
                        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                        {
                            dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
                            return;
                        }
        
                        dg_linkdefinition(
                            pBHarrayhead,
                            localswordlistid,
                            localwordid);
        
                        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                        {
                            dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
                            return;
                        }
        
                        numberoflocals++;
                    }
                }
            }
        }
    }

    // compile add n locals
    dg_compileaddnlocalstocallsubsframe(
        pBHarrayhead,
        numberoflocals);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
        return;
    }

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"number of locals = ");
    // dg_writestdoutuint64tohex(pBHarrayhead, numberoflocals);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

    // dg_printzerostring(pBHarrayhead, (unsigned char*)"start of initialized locals = ");
    // dg_writestdoutuint64tohex(pBHarrayhead, startofinitializedlocals);
    // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    // compile init each initialized local
    if (startofinitializedlocals != largestunsignedint)
    {
        i = numberoflocals;

        while (i > startofinitializedlocals)
        {
            i--;

            // dg_printzerostring(pBHarrayhead, (unsigned char*)"initializing local = ");
            // dg_writestdoutuint64tohex(pBHarrayhead, i);
            // dg_printzerostring(pBHarrayhead, (unsigned char*)", with offset ");
            // dg_writestdoutuint64tohex(pBHarrayhead, 0 - (((i + startreturnstackdepth) + 1) << 3));
            // dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

            dg_compiledatastacktobracketrbpd(
                pBHarrayhead,
                0 - (((i + startreturnstackdepth) + 1) << 3));

            
        }
    }

    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonreturnstackdepth,
        startreturnstackdepth + numberoflocals);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthcurlybracename);
        return;
    }
}

// dg_forthto
//  parse next word on line 
//  find word
//  get compile type
//  if compile type is fast local, local, or variable.... 
//   compile pop data stack and ! to that type

void dg_forthto (Bufferhandle* pBHarrayhead) // maybe make it always execute..... it's a compiling word....
{
    unsigned char* pname;
    UINT64 namelength;

    UINT64 wordid;

    Definitionheader* pdefinition;

    const char* state;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoname);
        return;
    }

    if (0 == namelength)
    {
        dg_pusherror(pBHarrayhead, dg_nowordfounderror);
        dg_pusherror(pBHarrayhead, dg_forthtoname);
        return;
    }

    wordid = dg_finddefinsearchorder (
        pBHarrayhead,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoname);
        return;
    }

    if (DG_ENDOFWORDLIST == wordid)
    {
        dg_pusherror(pBHarrayhead, dg_wordnotfoundinsearchordererror);
        dg_pusherror(pBHarrayhead, dg_forthtoname);
        return;
    }

    pdefinition = dg_getpdefinition (
        pBHarrayhead,
        wordid);

    if ( (DG_CORE_BUFFERID == pdefinition->compileroutinebuf) &&
         ((UINT64)&dg_forthdocompiletypedpushp == pdefinition->compileroutineoffset) )
    {
        // variable and probably any others...
        dg_executedefinition (
            pBHarrayhead,
            wordid);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        dg_pushdatastack(
            pBHarrayhead,
            (UINT64)&dg_forthstore);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        dg_pushdatastack(
            pBHarrayhead,
            (UINT64)DG_CORE_BUFFERID);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        dg_forthdocompiletypesubroutine(pBHarrayhead);  

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        return;
    }

    
    if ( (DG_CORE_BUFFERID == pdefinition->compileroutinebuf) &&
         ((UINT64)&dg_forthdocompiletypelocal == pdefinition->compileroutineoffset) )
    {
        dg_compilepushntodatastack (
            pBHarrayhead,
            pdefinition->dataoffset);
    
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }
    
        dg_compilecallcore (
            pBHarrayhead,
            (UINT64)(&dg_forthlocalsstore));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        return;
    }

    if ( (DG_CORE_BUFFERID == pdefinition->compileroutinebuf) &&
         ((UINT64)&dg_forthdocompiletypefastlocalfrom == pdefinition->compileroutineoffset) )
    {
        // fast local
        // throw error in execute state.... I think...
        
        state = (const char*)dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            statevariable);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthstatename);
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        if (state == dg_statecompile)
        {
            dg_compiledatastacktobracketrbpd(
                pBHarrayhead,
                pdefinition->dataoffset);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthtoname);
                return;
            }

            return;
        }

        if (state == dg_stateexecute)
        {
            dg_pusherror(pBHarrayhead, (const char*)" fast local only supported in compile state");
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        return;
    }

    if ( (DG_CORE_BUFFERID == pdefinition->compileroutinebuf) &&
         ((UINT64)&dg_forthdocompiletypevalue == pdefinition->compileroutineoffset) )
    {
        // be faster if I didn't pass parameters on the data stack...
        dg_docompiletypeostore(
            pBHarrayhead,
            pdefinition->databuf,
            pdefinition->dataoffset);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        return;
    }


    if ( (DG_CORE_BUFFERID == pdefinition->compileroutinebuf) &&
         ((UINT64)&dg_forthdocompiletypefvalue == pdefinition->compileroutineoffset) )
    {
        dg_docompiletypeof64store(
            pBHarrayhead,
            pdefinition->databuf,
            pdefinition->dataoffset);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        return;
    }

    if ( (DG_CORE_BUFFERID == pdefinition->compileroutinebuf) &&
         ((UINT64)&dg_forthdocompiletypetwovalue == pdefinition->compileroutineoffset) )
    {
        // be faster if I didn't pass parameters on the data stack...
        dg_docompiletypeotwostore(
            pBHarrayhead,
            pdefinition->databuf,
            pdefinition->dataoffset);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthtoname);
            return;
        }

        return;
    }

    
    dg_pusherror(pBHarrayhead, (const char*)" only VARIABLE VALUE FVALUE 2VALUE LOCALS| locals and { locals supported for now 2022 Jun 25");
    dg_pusherror(pBHarrayhead, dg_forthtoname);
    return;
}



void dg_forthvalue(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;

    UINT64 databufid;
    UINT64 databufoffset;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypevalue;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
    }

    databufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
    }

    // supposed to align here... 

    databufoffset = dg_getbufferlength(
        pBHarrayhead,
        databufid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
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
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
    }

    dg_forthcomma(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthvaluename);
        return;
    }
}


void dg_forthfvalue(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;

    UINT64 databufid;
    UINT64 databufoffset;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypefvalue;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
    }

    databufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
    }

    // supposed to align here... 

    databufoffset = dg_getbufferlength(
        pBHarrayhead,
        databufid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
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
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
    }

    dg_forthf64comma(pBHarrayhead); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfvaluename);
        return;
    }
}


void dg_forthtwovalue(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;

    UINT64 databufid;
    UINT64 databufoffset;

    UINT64 compilebufid = DG_CORE_BUFFERID;
    UINT64 compilebufoffset = (UINT64)&dg_forthdocompiletypetwovalue;

    UINT64 definition = DG_ENDOFWORDLIST;

    UINT64 vocabid;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }

    databufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }

    // supposed to align here... 

    databufoffset = dg_getbufferlength(
        pBHarrayhead,
        databufid);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }

    vocabid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilewordlist);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
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
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }

    dg_linkdefinition(
        pBHarrayhead,
        vocabid,
        definition);

    if (pBHarrayhead->errorcount != olderrorcount)
    {
        // probably should drop the definition here
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }

    dg_forthcomma(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }

    dg_forthcomma(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtwovaluename);
        return;
    }
}

