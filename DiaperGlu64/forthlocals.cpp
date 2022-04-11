// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.2.
//
//    DiaperGlu v5.2 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.2 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.2; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// April 10, 2022             //
// version 5.2                //
// /////////////////////////////



#include "diapergluforth.h"

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

// need word to empty locals wordlist and clear the using locals flag
// const char* dg_forthqueryclearlocalsname = "?CLEAR-LOCALS";

void dg_forthqueryclearlocals(Bufferhandle* pBHarrayhead)
{
    UINT64 localswordlistid;
    UINT64 usinglocalsflag;
    UINT64 usinglocallstringsflag;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
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
    
    usinglocalsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
		return;
    }
    
    usinglocallstringsflag = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalstringsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
		return;
    }
    
    // now clearing locals wordlist every time this function is called 8/9/2020
    //  this is so I can support local constants
    localswordlistid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
		return;
    }
    
    dg_prunehlistelement (
        pBHarrayhead,
        0, // hlistheaderid,
        localswordlistid); // elementheaderid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
        return;
    }
    
    if (FORTH_FALSE != usinglocalsflag)
    {
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
        
        // also need to compile call to restore local stack depth
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)(&dg_restorelocalstackdepth));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
            return;
        }
        
        dg_forthcompilecallcore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
            return;
        }
    }
    
    if (FORTH_FALSE != usinglocallstringsflag)
    {
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
        
        // also need to compile call to restore local lstring stack depth
        dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            (UINT64)(&dg_restorelocallsstackdepth));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
            return;
        }

        dg_forthcompilecallcore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthqueryclearlocalsname);
            return;
        }
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
