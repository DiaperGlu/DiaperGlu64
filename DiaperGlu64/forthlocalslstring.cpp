// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.8.
//
//    DiaperGlu v5.8 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.8 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.8; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// March 27, 2023             //
// version 5.8                //
// /////////////////////////////



#include "diapergluforth.h"

/*
const char* dg_savelocallsstackdepthname = "dg_savelocallsstackdepth";

void dg_savelocallsstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 locallstringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // get depth of locals lstring stack
    locallstringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocallsstackdepthname);
        return;
    }
    
    // save it to the depth stack
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID,
        locallstringstackdepth);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_savelocallsstackdepthname);
        return;
    }
        
    return;
}

const char* dg_restorelocallsstackdepthname = "dg_restorelocallsstackdepth";

void dg_restorelocallsstackdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 oldlocalslstringdepth;
    
    UINT64 currentlocalslstringdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    oldlocalslstringdepth = dg_popbufferuint64(
        pBHarrayhead, 
        DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocallsstackdepthname);
        return;
    }
    
    // doing this the slow way for now
    currentlocalslstringdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_restorelocallsstackdepthname);
        return;
    }
    
    while (currentlocalslstringdepth > oldlocalslstringdepth)
    {
        dg_droplstring (
            pBHarrayhead,
            DG_LOCALS_STRINGOFFSETSTACK_BUFFERID,
            DG_LOCALS_STRINGSTRINGSTACK_BUFFERID);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_restorelocallsstackdepthname);
            return;
        }
            
        currentlocalslstringdepth--;
    }

}
*/

const char* dg_forthlocalslstringfetchname = "LOCALSL$@";

void dg_forthlocalslstringfetch (Bufferhandle* pBHarrayhead)
// ( localindex -- )
// ( -$- u$ )
{
    UINT64 localsrelativeindex;
    UINT64 localsabsoluteindex;
    
    unsigned char* plocalslstring;
    UINT64 localslstringlength;
    
    UINT64 oldlocalsstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    
    localsrelativeindex = dg_popdatastack(pBHarrayhead);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringfetchname);
        return;
    }
    
    // get top value from locals depth stack
      // doing it the slow way right now
    oldlocalsstackdepth = dg_popbufferuint64(
        pBHarrayhead,
        DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringfetchname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID,
        oldlocalsstackdepth);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringfetchname);
        return;
    }
    
    // need to check for overflow
    if (localsrelativeindex > (largestunsignedint - oldlocalsstackdepth))
    {
        dg_pusherror(pBHarrayhead, dg_erroroverflow);
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringfetchname);
        return;
    }
    
    localsabsoluteindex = oldlocalsstackdepth + localsrelativeindex;

    plocalslstring = dg_getplstring(
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID,
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        localsabsoluteindex,
        &localslstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringfetchname);
        return;
    }
    
    dg_pushlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        localslstringlength,
        plocalslstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringfetchname);
        return;
    }
}


const char* dg_forthtolocalslstringname = ">LOCALSL$";

void dg_forthtolocalslstring(Bufferhandle* pBHarrayhead)
// ( u$ -$- )
// ( -localsL$- u$ )
{
    UINT64 stringstackdepth;
    
    unsigned char* plocalslstring;
    UINT64 localslstringlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtolocalslstringname);
        return;
    }
    
    if (0 == stringstackdepth)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtolocalslstringname);
        return;
    }
    
    plocalslstring = dg_getplstring(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        stringstackdepth - 1,
        &localslstringlength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtolocalslstringname);
        return;
    }
    
    dg_pushlstring (
        pBHarrayhead,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID,
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        localslstringlength,
        plocalslstring);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtolocalslstringname);
        return;
    }
    
    dg_droplstring(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthtolocalslstringname);
		return;
	}    
}


const char* dg_forthdocompiletypelocallsname = "dg_forthdocompiletypelocalls";

void dg_forthdocompiletypelocalls (Bufferhandle* pBHarrayhead)
//                         ( dataoffset databufid -- )
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_forthdrop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocallsname);
        return;
    }

    dg_forthliteral(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocallsname);
        return;
    }
    
    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(&dg_forthlocalslstringfetch));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocallsname);
        return;
    }

    dg_forthcompilecallcore(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdocompiletypelocallsname);
        return;
    }
}



const char* dg_forthlocalslstringbarname = "LOCALSL$|";

void dg_forthlocalslstringbar(Bufferhandle* pBHarrayhead)
{
    const char* pError;
    
//    UINT64 forthsemicolonnamelength = largestunsignedint;
//    UINT64 forthbarnamelength = largestunsignedint;
    
    UINT64 wordlength;
    unsigned char* pword;
    UINT64 foundendflag = FORTH_FALSE;
    
    UINT64 usinglocalstrings;
    
    INT64 compareflag;
    
    UINT64 relativeindex = 0;
    
    UINT64 localwordid;
    
    UINT64 localswordlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    localswordlistid = dg_getbufferuint64(pBHarrayhead, DG_DATASPACE_BUFFERID, dg_localswordlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
		return;
    }
/*    
    pError = dg_scanforbyte((unsigned char*)dg_forthsemicolonname, &forthsemicolonnamelength, 0);

    if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
		return;
	}
    
    pError = dg_scanforbyte((unsigned char*)dg_forthbarname, &forthbarnamelength, 0);

    if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanforbytename);
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
		return;
	}
*/    
    usinglocalstrings = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_colonhaslocalstringsflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
        return;
    }
    
    if (FORTH_FALSE == usinglocalstrings)
    {
        // compile call to save local lstring stack depth
        dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(&dg_savelocallsstackdepth));

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
            dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
            return;
        }

        dg_forthcompilecallcore(pBHarrayhead);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
            return;
        }

        // set using local lstrings flag
        dg_putbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_colonhaslocalstringsflag,
            FORTH_TRUE);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
            return;
        }
        
        relativeindex = 0;
    }
    else
    {
        relativeindex = dg_getbufferuint64(
            pBHarrayhead,
            DG_DATASPACE_BUFFERID,
            dg_numberoflocalstrings);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
            return;
        }
    }
        
    // parse words until you get | as the whole word - I'm gonna treat other words starting with | as not the end
    while(foundendflag == FORTH_FALSE)
    {
        pword = dg_parsewords(
            pBHarrayhead,
            &wordlength,
            (unsigned char)'|',
            &foundendflag,
            FORTH_FALSE);
 /*           
        dg_forthparseword (pBHarrayhead);
        // ( "<delimeters>word<delimeters>morestuff" -currentinputbuffer- "morestuff" )
        // ( -- addr length )
        
        wordlength = dg_popdatastack(pBHarrayhead);
        
        pword = (unsigned char*)dg_popdatastack(pBHarrayhead);
        
        // length = 0 is error
        if (0 == wordlength)
        {
            dg_pusherror(pBHarrayhead, dg_localsbarmissingerror);
            dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
            return;
        }
*/

        if (wordlength!= 0)
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
                dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
                return;
            }
                    
            if (0 == compareflag)
            {
                dg_pusherror(pBHarrayhead, dg_localsbarmissingerror);
                dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
                return;
            }
            /*        
            // | is end of locals
            pError = dg_comparebytes(
                pword,
                wordlength,
                (unsigned char*)dg_forthbarname,
                forthbarnamelength,
                &compareflag);
                        
            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_comparebytesname);
                dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
                return;
            }
                    
            if (0 == compareflag)
            {
                break;
            }
            */        
            // otherwise create a new word and compile call to push string to local lstrings
            // compile call to push n to local stack
            dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, (UINT64)(&dg_forthtolocalslstring));

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
                dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
                return;
            }

            dg_forthcompilecallcore(pBHarrayhead);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
                return;
            }
                    
            localwordid = dg_newwordcopyname (
                pBHarrayhead,
                (UINT64)DG_CORE_BUFFERID, 
                (UINT64)&dg_forthdocompiletypelocalls,
                0, // databufid,
                relativeindex, // databufoffset,
                (UINT64)DG_CORE_BUFFERID,
                (UINT64)pword,
                wordlength);
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
                return;
            }
                    
            dg_linkdefinition(pBHarrayhead, localswordlistid, localwordid);
                    
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
                return;
            }
                    
            relativeindex++;
        }
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_numberoflocalstrings,
        relativeindex);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlocalslstringbarname);
        return;
    }
}



