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


void dg_forthnewhlist (Bufferhandle* pBHarrayhead)
//     ( -- hlistid )
{   
    UINT64 hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_newhlist (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistname);
    }
    
    dg_pushdatastack (pBHarrayhead, hlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistname);
    }
}


void dg_forthfreehlist (Bufferhandle* pBHarrayhead)
//     ( hlistid -- )
{
    UINT64 hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreehlistname);
    }
    
    dg_freehlist (pBHarrayhead, hlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreehlistname);
    }
}


void dg_forthprunehlistelement(Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -- )
{
    UINT64 hlistid, elementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthprunehlistelementname);
        return;
    }
    
    elementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthprunehlistelementname);
        return;
    }
    
    dg_prunehlistelement (
        pBHarrayhead,
        hlistid,
        elementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthprunehlistelementname);
        return;
    }
}


void dg_forthfreehlistelement(Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -- )
{
    UINT64 hlistid, elementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreehlistelementname);
        return;
    }
    
    elementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreehlistelementname);
        return;
    }
    
    dg_prunehlistelement (
        pBHarrayhead,
        hlistid,
        elementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreehlistelementname);
        return;
    }
    
    dg_freehlistelement (
        pBHarrayhead,
        hlistid,
        elementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfreehlistelementname);
        return;
    }
}


// need to error case leave data stack intact like string stack
//  or need to string stack empty on error
void dg_forthnewhlistelement (Bufferhandle* pBHarrayhead)
//     ( parentelementid hlistid -- elementid )
//     ( value$ name$ -$- )
{
    UINT64 hlistid, parentelementid, stringstackdepth;
    
    unsigned char* pvalue;
    unsigned char* pname;
    
    UINT64 valuelength, namelength, newelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    valuelength = 0;
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
    }
    
    parentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }
    
    pvalue = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 2,
        &valuelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }

    pname = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }
    
    newelementid = dg_newhlistelement (
        pBHarrayhead,
        hlistid,
        parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        pname,
        namelength,
        pvalue,
        valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }

    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        newelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewhlistelementname);
        return;
    }
}


void dg_forthgethlistelementnom (Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -- )
//     ( -$- name$ )
{
    UINT64 elementid, hlistid;
    unsigned char* pname;
    UINT64 namelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementnomname);
        return;
    }
    
    elementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementnomname);
        return;
    }

    pname = dg_getshlistelementnom (
        pBHarrayhead,
        hlistid,
        elementid,
        &namelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementnomname);
        return;
    }
    
    dg_pushlstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        namelength,
        pname);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementnomname);
        return;
    }
}


void dg_forthgethlistelementvalue (Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -- )
//     ( -$- value$ )
{
    UINT64 elementid, hlistid;
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementvaluename);
        return;
    }
    
    elementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementvaluename);
        return;
    }

    pvalue = dg_getshlistelementvalue (
        pBHarrayhead,
        hlistid,
        elementid,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementvaluename);
        return;
    }
    
    dg_pushlstring(pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        valuelength,
        pvalue);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistelementvaluename);
        return;
    }
}


void dg_forthsethlistelementvalue (Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -- )
//     ( value$ -$- )
{
    UINT64 elementid, hlistid;
    unsigned char* pvalue;
    UINT64 valuelength;
    UINT64 stringstackdepth;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsethlistelementvaluename);
        return;
    }
    
    elementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsethlistelementvaluename);
        return;
    }

    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsethlistelementvaluename);
        return;
    }

    if (stringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsethlistelementvaluename);
        return;
    }

    pvalue = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 1,
        &valuelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsethlistelementvaluename);
        return;
    }
    
    dg_sethlistelementvalue (
        pBHarrayhead,
        hlistid,
        elementid,
        pvalue,
        valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsethlistelementvaluename);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsethlistelementvaluename);
        return;
    }
}


void dg_forthgethlistnewestchild (Bufferhandle* pBHarrayhead)
//     ( parentelementid hlistid -- childid )
{
    UINT64 parentelementid, elementid, hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewestchildname);
        return;
    }
    
    parentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewestchildname);
        return;
    }
    
    elementid = dg_gethlistlastchildofparent (
        pBHarrayhead,
        hlistid,
        parentelementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewestchildname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, elementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewestchildname);
        return;
    }
}


void dg_forthgethlistoldestchild (Bufferhandle* pBHarrayhead)
//     ( parentelementid hlistid -- childid )
{
    UINT64 parentelementid, elementid, hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldestchildname);
        return;
    }
    
    parentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldestchildname);
        return;
    }
    
    elementid = dg_gethlistfirstchild (
        pBHarrayhead,
        hlistid,
        parentelementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldestchildname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        elementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldestchildname);
        return;
    }
}


void dg_forthgethlistoldersibling (Bufferhandle* pBHarrayhead)
//     ( childelementid hlistid -- nextoldersiblingid )
{
    UINT64 childelementid, elementid, hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldersiblingname);
        return;
    }
    
    childelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldersiblingname);
        return;
    }
    
    elementid = dg_gethlistprevioussibling (
        pBHarrayhead,
        hlistid,
        childelementid);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldersiblingname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        elementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistoldersiblingname);
        return;
    }
}


void dg_forthgethlistnewersibling (Bufferhandle* pBHarrayhead)
//     ( parentelementid hlistid -- childid )
{
    UINT64 childelementid, elementid, hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewersiblingname);
        return;
    }
    
    childelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewersiblingname);
        return;
    }
    
    elementid = dg_gethlistnextsibling (
        pBHarrayhead,
        hlistid,
        childelementid);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewersiblingname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, elementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistnewersiblingname);
        return;
    }
}


void dg_forthchangehlistparent (Bufferhandle* pBHarrayhead)
// ( newparentelementid childelementid hlistid -- )
{
    UINT64 newparentelementid, elementid, hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthchangehlistparentname);
        return;
    }
    
    elementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthchangehlistparentname);
        return;
    }
    
    newparentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthchangehlistparentname);
        return;
    }
    
    dg_changehlistelementparent (
        pBHarrayhead,
        hlistid,
        elementid,
        newparentelementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthchangehlistparentname);
        return;
    }
}


void dg_forthgethlistparent (Bufferhandle* pBHarrayhead)
//     ( childelementid hlistid -- parentelementid )
{
    UINT64 childelementid, parentelementid, hlistid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistparentname);
        return;
    }
    
    childelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistparentname);
        return;
    }
    
    parentelementid = dg_gethlistelementparent (
        pBHarrayhead,
        hlistid,
        childelementid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistparentname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        parentelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistparentname);
        return;
    }
}


void dg_forthfindclosesthlistchild (Bufferhandle* pBHarrayhead)
//     ( parentelementid hlistid -- closestchildid sortkeyindexafterlastmatch compareflag )
//     ( name$ -$- )
{
    UINT64 parentelementid, hlistid;
    unsigned char* pname;
    UINT64 namelength;
    
    UINT64 stringstackdepth;
    
    UINT64 indexofkeyaftermatch;
    UINT64 foundsortkey;
    INT64 compareresultflag;
    
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
    
    parentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }

    if (stringstackdepth < 1)
    {
        // not enough strings to do compare, will push error and push not equal
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }

    pname = dg_getplstring(
        pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
    
    compareresultflag = dg_findsortedhlistchild (
        pBHarrayhead,
        pname,
        namelength,
        hlistid, 
        parentelementid,      
        &indexofkeyaftermatch, // index in sort key lstring after match
        &foundsortkey);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        foundsortkey);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        indexofkeyaftermatch);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        compareresultflag);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
}


void dg_forthfindhlistchild (Bufferhandle* pBHarrayhead)
//     ( parentelementid hlistid -- childid )
//     ( name$ -$- )
{
    UINT64 compareflag;
    UINT64 sortkeyindexafterlastmatch;
    UINT64 closestchildid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    dg_forthfindclosesthlistchild (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindhlistchildname);
        return;
    }
    
    compareflag = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindhlistchildname);
        return;
    }
    
    sortkeyindexafterlastmatch = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindhlistchildname);
        return;
    }
    
    closestchildid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindhlistchildname);
        return;
    }
    
    if (compareflag != 0)
    {
        closestchildid = DG_ENDOFLIST;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        closestchildid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindhlistchildname);
        return;
    }
}


void dg_forthhlisttoxmlstring (Bufferhandle* pBHarrayhead)
//     ( indentationstepsize rootelementid hlistid -- )
//     ( -$- dgluml$ )
{
    UINT64 hlistid;
    UINT64 rootelementid;
    UINT64 indentationstepsize;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhlisttoxmlstringname);
        return;
    }
    
    rootelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhlisttoxmlstringname);
        return;
    }
    
    indentationstepsize = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhlisttoxmlstringname);
        return;
    }
    
    dg_forthnewstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhlisttoxmlstringname);
        return;
    }

    dg_hlisttodglumlstring (
        pBHarrayhead,
        hlistid,
        rootelementid,
        indentationstepsize,
        0); // currentindentationlevel)
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfindclosesthlistchildname);
        return;
    }
}


void dg_forthgethowmanyhlistkids(Bufferhandle* pBHarrayhead)
// ( parentelementid hlistid -- numberofchildren )
{
    UINT64 hlistheaderid;
    UINT64 parentelementid;
    UINT64 numberofchildren;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistheaderid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethowmanyhlistkidsname);
        return;
    }
    
    parentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethowmanyhlistkidsname);
        return;
    }
    
    numberofchildren = dg_getnumberofsortedchildren(
        pBHarrayhead,
        hlistheaderid,
        parentelementid);
        
    dg_pushdatastack(pBHarrayhead, numberofchildren);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethowmanyhlistkidsname);
        return;
    }    
}


void dg_forthgethlistsortedchildn(Bufferhandle* pBHarrayhead)
//     ( n parentelementid hlistid -- childelementid )
{
    UINT64 hlistheaderid;
    UINT64 parentelementid;
    UINT64 n;
    UINT64 elementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistheaderid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistsortedchildnname);
        return;
    }
    
    parentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistsortedchildnname);
        return;
    }
    
    n = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistsortedchildnname);
        return;
    }
    
    elementid = dg_getidofsortedhlistchildn(
        pBHarrayhead,
        hlistheaderid,
        parentelementid,
        n);
        
    dg_pushdatastack(pBHarrayhead, elementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthgethlistsortedchildnname);
        return;
    }    
}


void dg_forthpackhlist(Bufferhandle* pBHarrayhead)
//     ( hlistid -- packedbufferid )
{
    UINT64 hlistid;
    UINT64 packedbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return;
    }
    
    packedbufferid = dg_packhlist(
        pBHarrayhead,
        hlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        packedbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_packhlistname);
        return;
    }
}


void dg_forthunpackhlist(Bufferhandle* pBHarrayhead)
//     ( packedbufferid -- hlistid )
{
    UINT64 hlistid;
    UINT64 packedbufferid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (olderrorcount == baderrorcount)
    {
        return;
    }
    
    packedbufferid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthunpackhlistname);
        return;
    }
    
    hlistid = dg_unpackhlist(
        pBHarrayhead,
        packedbufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthunpackhlistname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        hlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthunpackhlistname);
        return;
    }
}


void dg_forthtoeh(Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -- ) ( -H- elementid hlistid )
{
    UINT64* pbuflength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* pints = NULL;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoehname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthtoehname);
        return;
    }
    
    dg_pushbuffersegment(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        2 * sizeof(UINT64),
        pdatastack + (*pbuflength - (2*sizeof(UINT64))));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtoehname);
        return;
    }
    
    *pbuflength -= (2 * sizeof(UINT64));
}

void dg_forthehfrom(Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -H- ) ( -- elementid hlistid )
{
    UINT64* pbuflength = NULL;
    unsigned char* phstack = NULL;

    UINT64* pints = NULL;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehfromname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror); // this shows as 'not enough parameters' .. could be better
        dg_pusherror(pBHarrayhead, dg_forthehfromname);
        return;
    }
    
    dg_pushbuffersegment(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        2 * sizeof(UINT64),
        phstack + (*pbuflength - (2*sizeof(UINT64))));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehfromname);
        return;
    }
    
    *pbuflength -= 2 * sizeof(UINT64);
}


void dg_forthdropeh(Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -H- )
{
    UINT64* plength = NULL;
    unsigned char* pbuffer = NULL;
    
    pbuffer = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &plength);

    if (pbuffer == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdropehname);
        return;
    }

    if (*plength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdropehname);
        return;
    }

    *plength -= 2 * sizeof(UINT64);
}


void dg_forthehtop(Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -H- elementid hlistid ) ( -- elementid hlistid )
{
    UINT64* pbuflength = NULL;
    unsigned char* phstack = NULL;

    UINT64* pints = NULL;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehtopname);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehtopname);
        return;
    }
    
    dg_pushbuffersegment(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        2 * sizeof(UINT64),
        phstack + (*pbuflength - (2*sizeof(UINT64))));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehtopname);
        return;
    }
}


void dg_forthehnd(Bufferhandle* pBHarrayhead)
//     ( enhn ... e1h1 e0h0 -EH- enhn ... e1h1 e1h0 ) ( nd -- en hn )
{
    UINT64* pbuflength = NULL;
    unsigned char* phstack = NULL;

    UINT64* pints = NULL;
    
    UINT64 nd;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    nd = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehndname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehndname);
        return;
    }

    if (*pbuflength < ((nd+1) * 2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehndname);
        return;
    }
    
    dg_pushbuffersegment(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        2 * sizeof(UINT64),
        phstack + (*pbuflength - (nd+1) * 2 * sizeof(UINT64)));

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehndname);
        return;
    }
}


void dg_forthdupeh(Bufferhandle* pBHarrayhead)
//     ( elementid hlistid -H- elementid hlistid elementid hlistid )
{
    UINT64 bufferlength;
    UINT64* pbuflength = NULL;
    unsigned char* phstack = NULL;
    
    const char* pError;

    UINT64* pints = NULL;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    bufferlength = dg_getbufferlength(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdupehname);
        return;
    }
    
    if (bufferlength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthdupehname);
        return;
    }
    
    dg_growbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        2 * sizeof(UINT64),
        &pError,
        FORTH_FALSE);
    
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_forthdupehname);
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthdupehname);
        return;
    }
    
    pints = (UINT64*)(phstack + *pbuflength - (4*sizeof(UINT64)));
    
    pints[2] = pints[0];
    pints[3] = pints[1];
}


void dg_forthetoehtop(Bufferhandle* pBHarrayhead)
//     ( newelementid -- ) ( elementid hlistid -H- newelementid hlistid )
{
    UINT64* phstacklength = NULL;
    unsigned char* phstack = NULL;
    
    UINT64* pdatastacklength = NULL;
    unsigned char* pdatastack = NULL;

    UINT64* phstackints = NULL;
    UINT64* pdatastackints = NULL;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthetoehtopname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthetoehtopname);
        return;
    }
    
    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthetoehtopname);
        return;
    }

    if (*pdatastacklength < (sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthetoehtopname);
        return;
    }
    
    phstackints = (UINT64*)(phstack + *phstacklength - 2*sizeof(UINT64));
    pdatastackints = (UINT64*)(pdatastack + *pdatastacklength - sizeof(UINT64));
    
    phstackints[0] = pdatastackints[0];
    
    *pdatastacklength -= sizeof(UINT64);
}


void dg_forthehnewelement(Bufferhandle* pBHarrayhead)
{
    UINT64* phstacklength = NULL;
    unsigned char* phstack = NULL;
    
    UINT64 stringstackdepth;
    unsigned char* pvalue;
    unsigned char* pname;
    UINT64 namelength, valuelength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }
    
    pvalue = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 2,
        &valuelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }

    pname = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        *((UINT64*)(phstack + *phstacklength - sizeof(UINT64))), // hlistid,
        *((UINT64*)(phstack + *phstacklength - (2*sizeof(UINT64)))), // parentelementid, /
        pname,
        namelength,
        pvalue,
        valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }

    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementname);
        return;
    }
}


void dg_forthehnewelementtoeh(Bufferhandle* pBHarrayhead)
{
    UINT64* phstacklength = NULL;
    unsigned char* phstack = NULL;
    
    UINT64 stringstackdepth;
    unsigned char* pvalue;
    unsigned char* pname;
    UINT64 namelength, valuelength;
    
    UINT64 myhlistid, myelementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + *phstacklength - sizeof(UINT64)));
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
    
    if (stringstackdepth < 2)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
    
    pvalue = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 2,
        &valuelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }

    pname = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
    
    myelementid = dg_newhlistelement (
        pBHarrayhead,
        myhlistid, // hlistid,
        *((UINT64*)(phstack + (*phstacklength - (2*sizeof(UINT64))))), // parentelementid, /
        pname,
        namelength,
        pvalue,
        valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }

    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
    
    dg_pushbufferuint64(pBHarrayhead, DG_EHSTACK_BUFFERID, myelementid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
    
    dg_pushbufferuint64(pBHarrayhead, DG_EHSTACK_BUFFERID, myhlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnewelementtoehname);
        return;
    }
}


void dg_forthnamestrtovaluestr(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    UINT64 stringstackdepth;
    
    UINT64 hlistid;
    UINT64 elementid;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }
    
    elementid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }
    
    if (stringstackdepth < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }

    pname = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }
    
    pvalue = dg_namestringtovaluestring(
        pBHarrayhead,
        hlistid,
        elementid,
        pname,
        namelength,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }
    
    dg_pushlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // stringbufferid,
        valuelength, // UINT32 length,
        pvalue); // unsigned char* psrc)
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluestrname);
        return;
    }
}


void dg_forthnamestrtovalue(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    UINT64 stringstackdepth;
    
    UINT64 hlistid;
    UINT64 elementid;
    
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
    
    elementid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
    
    stringstackdepth = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
    
    if (stringstackdepth < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }

    pname = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        stringstackdepth - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
    
    pvalue = dg_namestringtovaluestring(
        pBHarrayhead,
        hlistid,
        elementid,
        pname,
        namelength,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
    
    x = *((UINT64*)pvalue);
    
    dg_forthdropstring(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
    
    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, x);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamestrtovaluename);
        return;
    }
}


void dg_forthehnamestrtovaluestr(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    dg_forthehtop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamestrtovaluestrname);
        return;
    }
    
    dg_forthnamestrtovaluestr(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamestrtovaluestrname);
        return;
    }
}


void dg_forthehnamestrtovalue(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    dg_forthehtop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamestrtovaluename);
        return;
    }
    
    dg_forthnamestrtovalue(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamestrtovaluename);
        return;
    }
}


void dg_forthnamewtovaluestr(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    
    UINT64 hlistid;
    UINT64 elementid;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
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
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluestrname);
        return;
    }
    
    elementid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluestrname);
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluestrname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluestrname);
        return;
    }
    
    pvalue = dg_namestringtovaluestring(
        pBHarrayhead,
        hlistid,
        elementid,
        pname,
        namelength,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluestrname);
        return;
    }
    
    dg_pushlstring (
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, // offsetbufferid,
        DG_STRINGSTRINGSTACK_BUFFERID, // stringbufferid,
        valuelength, // UINT32 length,
        pvalue); // unsigned char* psrc)
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluestrname);
        return;
    }
}


void dg_forthnamewtovalue(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;

    UINT64 hlistid;
    UINT64 elementid;
    
    unsigned char* pvalue;
    UINT64 valuelength;
    
    UINT64 x;
    
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
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluename);
        return;
    }
    
    elementid = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluename);
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluename);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluename);
        return;
    }
    
    pvalue = dg_namestringtovaluestring(
        pBHarrayhead,
        hlistid,
        elementid,
        pname,
        namelength,
        &valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluename);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluename);
        return;
    }
    
    x = *((UINT64*)pvalue);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        x);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnamewtovaluename);
        return;
    }
}


void dg_forthehnamewtovaluestr(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    dg_forthehtop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamewtovaluestrname);
        return;
    }
    
    dg_forthnamewtovaluestr(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamewtovaluestrname);
        return;
    }
}


void dg_forthehnamewtovalue(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        // could not get error count because BHarrayhead is not there so just exiting
        return;
    }
    
    dg_forthehtop(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamewtovaluename);
        return;
    }
    
    dg_forthnamewtovalue(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehnamewtovaluename);
        return;
    }
}


void dg_forthehoherewtonewelement(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 myhlistid;
    UINT64 mysymbollistelementid;
    UINT64 x;
    UINT64 mycurrentcompilebufferid;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthehoherewtonewelementname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehoherewtonewelementname);
        return;
    }

    if (*phstacklength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehoherewtonewelementname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    mysymbollistelementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
 
    
    mycurrentcompilebufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehoherewtonewelementname);
        return;
    }
    
    x = dg_getbufferlength(
        pBHarrayhead,
        mycurrentcompilebufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehoherewtonewelementname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myhlistid,
        mysymbollistelementid, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        pname, // pcib + ciboldoffset,   // unsigned char* pname,
        namelength,             // UINT32 namelength,
        (unsigned char*)&x, // unsigned char* pvalue,
        sizeof(UINT64)); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehoherewtonewelementname);
        return;
    }
}


void dg_forthehdot(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 hlistid;
    UINT64 elementid;
    
    unsigned char* pvaluestring;
    UINT64 valuelength;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthehdotname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehdotname);
        return;
    }

    if (*phstacklength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehdotname);
        return;
    }
    
    hlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    elementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
 
    pvaluestring = dg_namestringtovaluestring(
        pBHarrayhead,
        hlistid,
        elementid,
        pname,
        namelength,
        &valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehdotname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_forthehdotname);
    }
    
    dg_pushdatastack(pBHarrayhead, *((UINT64*)pvaluestring));
}


void dg_forthehbracketnddot(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 hlistid;
    UINT64 elementid;
    
    unsigned char* pvaluestring;
    UINT64 valuelength;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64* pints;
    
    UINT64 nd;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    nd = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }
 
    if ( (UINT64)largestunsignedint == nd )
    {
        // calculation will overflow
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }   
 
    if ( (nd + 1) > (largestunsignedint / (2 * sizeof(UINT64)) ) )
    {
        // calculation will overflow
        dg_pusherror(pBHarrayhead, dg_indexnotinarrayerror);
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }   

    if ( *phstacklength < ((nd + 1) * (2 * sizeof(UINT64))) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }
 
    pints = (UINT64*)( (phstack + (*phstacklength)) - ((nd + 1) * (2 * sizeof(UINT64))) );
    
    hlistid = pints[1];
    elementid = pints[0];
 
    pvaluestring = dg_namestringtovaluestring(
        pBHarrayhead,
        hlistid,
        elementid,
        pname,
        namelength,
        &valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }
    
    if (valuelength < sizeof(UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
    }
    
    dg_pushdatastack(pBHarrayhead, *((UINT64*)pvaluestring));
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehbracketnddotname);
        return;
    }
}


void dg_forthehbracket1ddot(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, 1);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehbracket1ddotname);
        return;
    }
    
    dg_forthehbracketnddot(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthehbracket1ddotname);
        return;
    }
}


void dg_forthsymbolenumcurly (Bufferhandle* pBHarrayhead)
{
    UINT64 valuejustsetflag = FORTH_TRUE;
    UINT64 value;        
    UINT64 stepsize; 
    
    UINT64 data;
    UINT64 base;
    UINT64 foundendflag = FORTH_FALSE;
    UINT64 flag;
    UINT64 numbersinarow = 0;
    
    UINT64 parentelementid;
    UINT64 parenthlistid;

    unsigned char* pname;
    UINT64 namelength = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    parenthlistid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
        return;
    }
    
    parentelementid = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
        return;
    }
    
    value = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
        return;
    }
    
    stepsize = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
        return;
    }
    
    base = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        basevariable);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthbasename);
        dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
        return;
    }
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
            return;
        }

        if (namelength != 0)
        {
            // this is a signed conversion, a - sign in front of the number is acceptable
            data = dg_pchartonumber(
                pname,
                namelength,
                base,
                &flag); // this routine doesn't return errors

            if (flag != FORTH_FALSE)
            {
                switch (numbersinarow)
                {
                    case 0:
                        stepsize = data;
                        break;
                    case 1:
                        value = data;
                        valuejustsetflag = FORTH_TRUE;
                        break;
                    default:
                        dg_pusherror(pBHarrayhead, dg_toomanyparameterserror);
                        dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
                        return;
                }
                
                numbersinarow++;
            }
            else
            {
                numbersinarow = 0;
                
                if (valuejustsetflag == FORTH_FALSE)
                {
                    value += stepsize;
                }
                else
                {
                    valuejustsetflag = FORTH_FALSE;
                }
                
                dg_newhlistelement (
                    pBHarrayhead,
                    parenthlistid,
                    parentelementid, 
                    pname,   
                    namelength,             
                    (unsigned char*)&value, 
                    sizeof(UINT64)); 

                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
                    return;
                }
            }
        }
    }
    
    if (valuejustsetflag == FORTH_FALSE)
    {
        value += stepsize;
    }
    else
    {
        valuejustsetflag = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, value);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthsymbolenumcurlyname);
        return;
    }
}


void dg_forthosymbolcodeimportscommacurly(Bufferhandle* pBHarrayhead)
{
    UINT64 value;         
    
    UINT64 foundendflag = FORTH_FALSE;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64 parentelementid;
    UINT64 parenthlistid;
    
    UINT64 myccbufid;

    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64* pints;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthosymbolcodeimportscommacurlyname);
        return;
    }

    if ( *phstacklength < (2 * (2 * sizeof(UINT64))) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthosymbolcodeimportscommacurlyname);
        return;
    }
 
    pints = (UINT64*)( (phstack + (*phstacklength)) - (2 * (2 * sizeof(UINT64))) );
    
    parenthlistid = pints[1];
    parentelementid = pints[0];
    
    while(foundendflag == FORTH_FALSE)
    {
        pname = dg_parsewords(
            pBHarrayhead,
            &namelength,
            (unsigned char)'>',
            &foundendflag,
            FORTH_FALSE);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthosymbolcodeimportscommacurlyname);
            return;
        }

        if (namelength != 0)
        {
            // compile the link
            value = dg_compilecodelink(pBHarrayhead);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthosymbolcodeimportscommacurlyname);
                return;
            }
               
            dg_newhlistelement (
                pBHarrayhead,
                parenthlistid,
                parentelementid, 
                pname,   
                namelength,             
                (unsigned char*)&value, 
                sizeof(UINT64)); 

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthosymbolcodeimportscommacurlyname);
                return;
            }
        }
    }
}


void dg_forthnewflatosymbolbuf(Bufferhandle* pBHarrayhead)
{
    UINT64 oldcompilebuf;
    UINT64 bufid;
    UINT64 hlistid;
    UINT64 importparentelementid;
    UINT64 exportparentelementid;
    // UINT64 x86wordlistid;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    oldcompilebuf = dg_getbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
        
    // new current compile buffer
    bufid = dg_newbuffer (
        pBHarrayhead,
        0x10000,      // growby,
        (UINT64)largestunsignedint,   // maxsize,
        &pError,
        FORTH_FALSE);  // force error
  
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    dg_putbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer,   // offset
        bufid);                 // data);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
          
    // new hlist
    hlistid = dg_newhlist (pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    // make 2 top hlist elements for import and export symbol lists
    importparentelementid = dg_newhlistelement (
        pBHarrayhead,
        hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"imports",   // pname,  // name doesn't matter
        7,                           // namelength,
        (unsigned char*)"",          // pvalue, // value doesn't matter
        0);                          // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
        
    exportparentelementid = dg_newhlistelement (
        pBHarrayhead,
        hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"exports",   // pname,  // name doesn't matter
        7,                           // namelength,
        (unsigned char*)"",          // pvalue, // value doesn't matter
        0);                          // valuelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    // push import and export symbol ehs to eh stack
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        importparentelementid);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        hlistid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        exportparentelementid);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        hlistid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    // save old compile buffer on rstack
    dg_pushbufferuint64 (
        pBHarrayhead,
        DG_RSTACK_BUFFERID,
        oldcompilebuf);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
        return;
    }
    
    // x86wordlistid = dg_getbufferuint64(
    //    pBHarrayhead,
    //    DG_DATASPACE_BUFFERID,
    //    dg_cpux86vocabid);
        
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {       
    //    dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
    //    return;
    // }
    
    // dg_pushbufferuint64 (
    //    pBHarrayhead,
    //    DG_SEARCHORDERSTACK_BUFFERID,
    //    x886wordlistid);
        
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {       
    //    dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
    //    return;
    // }
}


void dg_forthfreeflatosymbolbuf(Bufferhandle* pBHarrayhead)
{
    UINT64 bufid;
    UINT64 hlistid;
    UINT64 oldcompilebufid;
    // UINT64 x86wordlistid;
    // UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    bufid = dg_getbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    oldcompilebufid = dg_popbufferuint64(
        pBHarrayhead,
        DG_RSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    dg_putbufferuint64 (
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer,   // offset
        oldcompilebufid);                 // data);
  
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    hlistid = dg_popbufferuint64(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    dg_popbufferuint64(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    dg_popbufferuint64(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    dg_popbufferuint64(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    dg_freebuffer (
        pBHarrayhead,
        bufid);
    
    // no error from this function
    
    dg_freehlist (
        pBHarrayhead,
        hlistid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {       
        dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
        return;
    }
    
    // x86wordlistid = dg_getbufferuint64(
    //     pBHarrayhead,
    //     DG_DATASPACE_BUFFERID,
    //     dg_cpux86vocabid);
        
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {       
    //    dg_pusherror(pBHarrayhead, dg_forthnewflatosymbolbufname);
    //    return;
    // }
    
    // x = dg_popbufferuint64(
    //    pBHarrayhead,
    //    DG_SEARCH_ORDER_STACK_BUFFERID);
        
    // if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    // {       
    //    dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
    //    return;
    // }
    
    // if (x != x86wordlistid)
    // {
    //    dg_pushbufferuint64(pBHarrayhead, DG_SEARCH_ORDER_STACK_BUFFERID, x);
    //    dg_pusherror(pBHarrayhead, (const char*)" error dropping x86wordlist from search order. It wasn't the x86 wordlist on top of the search order.");
    //    dg_pusherror(pBHarrayhead, dg_forthfreeflatosymbolbufname);
    //    return;
    // }
}


void dg_forthsymbol(Bufferhandle* pBHarrayhead)
{
    // ( N -- )
    // ( "<spaces>symbolname<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )

    unsigned char* pname;
    UINT64 namelength = 0;

    // Bufferhandle* pBH = NULL;
    
    UINT64 myhlistid;
    UINT64 mysymbollistelementid;
    UINT64 x;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthsymbolname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsymbolname);
        return;
    }

    if (*phstacklength < (2 * sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsymbolname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    mysymbollistelementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
  
    x = dg_popbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolname);
        return;
    }
    
    dg_newhlistelement (
        pBHarrayhead,
        myhlistid,
        mysymbollistelementid, // parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        pname, // pcib + ciboldoffset,   // unsigned char* pname,
        namelength,             // UINT64 namelength,
        (unsigned char*)&x, // unsigned char* pvalue,
        sizeof(UINT64)); // UINT64 valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsymbolname);
        return;
    }
}


// on windows, you need to compile some stuff first...
//  and put the offset in...
void dg_forthosymbolimport(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64* pints;
    
    UINT64 mycurrentcompilebufferid;
    UINT64 x;
    
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
        dg_pusherror(pBHarrayhead, dg_forthosymbolimportname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthosymbolimportname);
        return;
    }
 
    x = dg_compileosymbolimportstuff(pBHarrayhead); // returns the offset of the link

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolimportname);
        return;
    }
 
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthosymbolimportname);
        return;
    }

    if ( *phstacklength < (2 * (2 * sizeof(UINT64))) )
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthosymbolimportname);
        return;
    }
 
    pints = (UINT64*)( (phstack + (*phstacklength)) - (2 * (2 * sizeof(UINT64))) );
 
    dg_newhlistelement (
        pBHarrayhead,
        pints[1], // parenthlistid,
        pints[0], // parentelementid, 
        pname,
        namelength,
        (unsigned char*)&x, // pvalue,
        sizeof(UINT64)); // valuelength);   
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolimportname);
        return;
    }
}

void dg_forthosymbolentry(Bufferhandle* pBHarrayhead)
{
    unsigned char* pname;
    UINT64 namelength = 0;
    
    UINT64 myhlistid;
    UINT64 mysymbollistelementid;
    UINT64 x;
    UINT64 mycurrentcompilebufferid;

    UINT64 newelementid;
    
    unsigned char* phstack;
    UINT64* phstacklength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
    
    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthosymbolentryname);
        return;
    }
    
    phstack = dg_getpbuffer(
        pBHarrayhead,
        DG_EHSTACK_BUFFERID,
        &phstacklength);

    if (phstack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthhstackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthosymbolentryname);
        return;
    }

    if (*phstacklength < 2 * sizeof (UINT64))
    {
        dg_pusherror(pBHarrayhead, dg_underflowerror);
        dg_pusherror(pBHarrayhead, dg_forthosymbolentryname);
        return;
    }
    
    myhlistid = *((UINT64*)(phstack + ((*phstacklength) - sizeof(UINT64))));
    
    mysymbollistelementid = *((UINT64*)(phstack + ((*phstacklength) - (2 * sizeof(UINT64)))));
 
    
    mycurrentcompilebufferid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentcompilebuffer);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolentryname);
        return;
    }
    
    x = dg_getbufferlength(
        pBHarrayhead,
        mycurrentcompilebufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolentryname);
        return;
    }
    
    newelementid = dg_newhlistelement (
        pBHarrayhead,
        myhlistid,
        mysymbollistelementid,  // parentelementid, 
        pname,                  // pname = pcib + ciboldoffset,   
        namelength,             // namelength,
        (unsigned char*)&x,     // pvalue,
        sizeof(UINT64));        // valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolentryname);
        return;
    }

    // adding a child named ENTRY with no value
    newelementid = dg_newhlistelement (
        pBHarrayhead,
        myhlistid,
        newelementid,            // parentelementid,
        (unsigned char*)"ENTRY", // pname,
        5,                       //namelength,
        (unsigned char*)&x,      // pvalue,
        0);                      // valuelength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthosymbolentryname);
        return;
    }
}

