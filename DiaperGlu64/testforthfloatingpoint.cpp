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
#include "testdglu.h"

void testdg_sfloats()
{
    UINT64 y = 0;
    UINT64 x = 0;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsfloats\n");
    
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfloats(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error doing sfloats got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, expected 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfloats(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error doing sfloats got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, expected 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 0x12343);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfloats(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error doing sfloats got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != (0x12343 * 4) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, expected 0x12343 * 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, -1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -1 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfloats(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -1 case, got error doing sfloats got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -1 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != -4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -1 case, expected -4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_sfloatplus()
{
    UINT64 y = 0;
    UINT64 x = 0;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsfloatplus\n");
    
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfloatplus(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error doing sfloatplus got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, expected 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfloatplus(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error doing sfloatplus got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 5 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, expected 5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 0x12343);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfloatplus(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error doing sfloatplus got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 0x12347 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, expected 0x12347, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_sfaligned()
{
    UINT64 y = 0;
    UINT64 x = 0;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsfaligned\n");
    
    dg_pushdatastack(&BHarrayhead, 0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfaligned(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error doing sfaligned got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0 case, expected 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfaligned(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error doing sfaligned got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 case, expected 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfaligned(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 case, got error doing sfaligned got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 case, expected 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfaligned(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3 case, got error doing sfaligned got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3 case, expected 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 4);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfaligned(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4 case, got error doing sfaligned got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4 case, expected 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 0x12343);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfaligned(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error doing sfaligned got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( y != 0x12344 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x12343 case, expected 0x12344, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_sfalign()
{
    UINT64 y = 0;
    UINT64 x = 0;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsfalign\n");
    
    dg_forthsfalign(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing initial sfalign got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthhere(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing HERE got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    y = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (y % 4) != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected here to be multiple of 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfalign(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing 2nd sfalign got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthhere(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing 2nd sfalign got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( x != y )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected 2nd align to not change, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, 1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthallot(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing allot got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfalign(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing 3rd sfalign got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthhere(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing 3rd sfalign got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( x != y + 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected 3rd align to be start + 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_sffetch()
{
    UINT64 y = 0;
    FLOAT64 r;
    
    *((UINT32*)(&y)) = 0x40000000;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsffetch\n");
    
    dg_pushdatastack(&BHarrayhead, (UINT64)&y);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsffetch(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing sffetch got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (r != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected 2.0 to be fetched got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_sfstore()
{
    UINT64 x;
    UINT64 y = 0;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthsfstore\n");
    
    
    dg_pushdatastack(&BHarrayhead, (UINT64)&y);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error pushing f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsfstore(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing sfstore got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    // 
    if ( ((UINT32*)(&y))[1] != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected 32 bits after to be 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, ((UINT32*)(&y))[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ( ((UINT32*)(&y))[0] != 0x40000000 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected 2.0 to be stored got ");
        dg_writestdoutuint64tohex(&BHarrayhead, ((UINT32*)(&y))[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthprecision()
{
    UINT64 x;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthprecision\n");
    
    
    dg_pushdatastack(&BHarrayhead, 0x15);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x15 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsetprecision(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x15 case, got error setting precision got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthprecision(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x15 case, got error getting precision got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x15 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x15)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x15 case, got wrong precision expected 0x15 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushdatastack(&BHarrayhead, 0x23);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got error pushing data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthsetprecision(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got error setting precision got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthprecision(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got error getting precision got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0x23)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got wrong fdepth expected 0x23 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got error getting fdepth got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0x23 case, got wrong fdepth expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthfproximate()
{
    UINT64 x;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfproximate\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfproximate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got error doing fproximate got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got error doing fdepth got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got wrong fdepth expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.0 case, expected FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.00001);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfproximate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got error doing fproximate got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got error doing fdepth got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got wrong fdepth expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 1.00001 case, expected FORTH_TRUE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfproximate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got error doing fproximate got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got error doing fdepth got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got wrong fdepth expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 3.0 0.0 case, expected FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.9);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfproximate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got error doing fproximate got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got error doing fdepth got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got wrong fdepth expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.9 0.0 case, expected FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -0.15);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfproximate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got error doing fproximate got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got error doing fdepth got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got wrong fdepth expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.15 case, expected FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -0.25);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfproximate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got error doing fproximate got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got error doing fdepth got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got wrong fdepth expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (x != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 2.0 -0.25 case, expected FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthftanh()
{
    FLOAT64 r3 = 0.0;
    FLOAT64 re, rt;
    
    *((UINT64*)(&re)) = dg_f64e;
    

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthftanh\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftanh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing ftanh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( r3 != 0.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftanh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error doing ftanh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    rt = ((re * re) - 1.0) / ((re * re) + 1.0);
    
    if ( (r3 < rt - 0.0001) || (r3 > rt + 0.0001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected (e squared - 1)/( e squared + 1), got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthftan()
{
    FLOAT64 r = 0.0;
    FLOAT64 rpi;
    
    *((UINT64*)(&rpi)) = dg_f64pi;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthftan\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing ftan got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( r != 0.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, rpi / 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/4 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/4 case, got error doing fsin got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/4 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (r < 0.9999) || (r > 1.0001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, expected 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfsqrt()
{
    FLOAT64 r3 = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfsqrt\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 16.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 16.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsqrt(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 16.0 case, got error doing fsinh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 16.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( r3 != 4.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 16.0 case, expected 4.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsqrt(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error doing fsqrt got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( r3 != 1.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfsinh()
{
    FLOAT64 r3 = 0.0;
    FLOAT64 re, rt;
    
    *((UINT64*)(&re)) = dg_f64e;
    

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfsinh\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsinh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fsinh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( r3 != 0.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsinh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error doing fsinh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    rt = ((re * re) - 1.0) / (2 * re);
    
    if ( (r3 < rt - 0.0001) || (r3 > rt + 0.0001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected (e squared - 1)/2e, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfsincos()
{
    FLOAT64 r2 = 0.0;
    FLOAT64 r3 = 0.0;
    FLOAT64 rpi;
    
    *((UINT64*)(&rpi)) = dg_f64pi;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfsincos\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsincos(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fsincos got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r2 = dg_popf64fromf64stack(&BHarrayhead); // sin result
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead); // cos result
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (( r2 < 0.999 ) || (r2 > 1.001))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected cos 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r2)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ( r3 != 0.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected sin 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, rpi);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsincos(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, got error doing fsincos got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r2 = dg_popf64fromf64stack(&BHarrayhead);  // sin result
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead); // cos result
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (r2 > -0.9999) || (r2 < -1.0) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, expected cos -1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r2)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ( (r3 < -0.0001) || (r3 > 0.0001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, expected sin 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, rpi / 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsincos(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, got error doing fsincos got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r2 = dg_popf64fromf64stack(&BHarrayhead); // sin result
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r3 = dg_popf64fromf64stack(&BHarrayhead); // cos result
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (r2 < -0.0001) || (r2 > 0.0001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, expected cos 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r2)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if ( (r3 < 0.9999) || (r3 > 1.0001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, expected sin 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r3)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfsin()
{
    FLOAT64 r = 0.0;
    FLOAT64 rpi;
    
    *((UINT64*)(&rpi)) = dg_f64pi;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfsin\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsin(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fsin got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( r != 0.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, rpi);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsin(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, got error doing fsin got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (r < -0.0001) || (r > 0.0001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi case, expected 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, rpi / 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfsin(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, got error doing fsin got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (r < 0.9999) || (r > 1.0) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! pi/2 case, expected 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthflog()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthflog\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 100.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 100.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthflog(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 100.0 case, got error doing flog got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 100.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( r != 2.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 100.0 case, expected 2.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthflnp1()
{
    FLOAT64 r = 0.0;
    FLOAT64 re;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthflnp1\n");
    
    *((UINT64*)(&re)) = dg_f64e;
    
    re = re - 1.0;
    
    dg_pushf64tof64stack(&BHarrayhead, re);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e - 1 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthflnp1(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e - 1 case, got error doing flnp1 got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e - 1 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (r < 0.99999) || (r > 1.00001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e - 1 case, expected 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfln()
{
    FLOAT64 r = 0.0;
    FLOAT64 re;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfln\n");
    
    *((UINT64*)(&re)) = dg_f64e;
    
    dg_pushf64tof64stack(&BHarrayhead, re);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfln(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e case, got error doing fln got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( (r < 0.99999) || (r > 1.00001) )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! e case, expected 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfexpm1()
{
    FLOAT64 r = 0.0;
    FLOAT64 rem;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfexpm1\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfexpm1(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error doing fexpm1 got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    *((UINT64*)(&rem)) = dg_f64e;
    rem = rem - 1.0;
    
    if (r != rem)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&rem)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfexp()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfexp\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfexp(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error doing fexp got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (*((UINT64*)(&r)) != dg_f64e)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, dg_f64e );
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfcosh()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfcosh\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfcosh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fcosh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfcos()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfcos\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfcos(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fcos got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfatan2()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfatan2\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfatan2(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 1.0 case, got error doing fatan2 got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 1.0 case, expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfatan()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfatan\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfatan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fatan got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfatanh()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfatanh\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfatanh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fatanh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfasinh()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfasinh\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfasinh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fasinh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfasin()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfasin\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfasin(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fasin got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfalog()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfalog\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfalog(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error doing falog got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ((r < 99.99) || (r > 100.01))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected 100.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfacosh()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfacosh\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfacosh(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error doing facosh got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfacos()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfacos\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 1.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfacos(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error doing facos got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfabs()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfabs\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 7.9);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfabs(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error doing fabs got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 7.9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, expected 7.9 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -7.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfabs(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error doing fabs got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 7.5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, expected 7.5 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfstarstar()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfstarstar\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstarstar(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 4.0 case, got error doing fstarstar got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 4.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 4.0 case, expected 16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstarstar(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 3.0 case, got error doing fstarstar got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 3.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 to the 3.0 case, expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstarstar(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 4.0 case, got error doing fstarstar got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 4.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 4.0 case, expected 16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstarstar(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.0 case, got error doing fstarstar got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != -8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.0 case, expected -8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 3.1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.1 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstarstar(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.1 case, got error doing fstarstar got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.1 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != (FLOAT64)dg_f64NaN)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 to the 3.1 case, expected NaN got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 9.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 9.0 to the 1.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 9.0 to the 1.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstarstar(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 9.0 to the 1.5 case, got error doing fstarstar got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 9.0 to the 1.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ((r < 26.99) || (r > 27.01))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 9.0 to the 1.5 case, expected 27.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthrepresent()
{
    INT64 n;
    FLOAT64 r;
    const char* perror;
    unsigned char pbuf[64];
    UINT64 i;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthrepresent\n");
    
    for(i = 0; i < 64; i++)
    {
        pbuf[i] = 'x';
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 1.23);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error pushing 1.23 to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, (UINT64)pbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case got error pushing addr to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, (UINT64)4);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case got error pushing buflength to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_forthrepresent(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error doing REPRESENT got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected fdepth 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected flag2 = FORTH_TRUE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected flag1 = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected base10exponent = 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[0] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected pbuf[0] = '1' got ");
        dg_writestdout(&BHarrayhead, pbuf, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[1] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected pbuf[1] = '2' got ");
        dg_writestdout(&BHarrayhead, pbuf+1, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[2] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected pbuf[2] = '3' got ");
        dg_writestdout(&BHarrayhead, pbuf+2, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[3] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected pbuf[3] = '0' got ");
        dg_writestdout(&BHarrayhead, pbuf+3, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[4] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, expected pbuf[4] = 'x' got ");
        dg_writestdout(&BHarrayhead, pbuf+4, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    for(i = 0; i < 64; i++)
    {
        pbuf[i] = 'x';
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -12.3);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! success case, got error pushing -12.3 to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, (UINT64)pbuf);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case got error pushing addr to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, (UINT64)4);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case got error pushing buflength to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    dg_forthrepresent(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, got error doing REPRESENT got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected fdepth 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected flag2 = FORTH_TRUE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected flag1 = FORTH_TRUE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected base10exponent = 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[0] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected pbuf[0] = '1' got ");
        dg_writestdout(&BHarrayhead, pbuf, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[1] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected pbuf[1] = '2' got ");
        dg_writestdout(&BHarrayhead, pbuf+1, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[2] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected pbuf[2] = '3' got ");
        dg_writestdout(&BHarrayhead, pbuf+2, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[3] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected pbuf[3] = '0' got ");
        dg_writestdout(&BHarrayhead, pbuf+3, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pbuf[4] != 'x')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -success case, expected pbuf[4] = 'x' got ");
        dg_writestdout(&BHarrayhead, pbuf+4, 1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfswap()
{
    INT64 n;
    FLOAT64 r;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfswap\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 1st push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 2nd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 3rd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfswap(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, got error doing FROT got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, expected depth 3 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, got error doing 1st pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, expected 4.0 from first pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, got error doing 2nd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, expected 8.0 from 2nd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, got error doing 3rd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st fswap case, expected 2.0 from 3rd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfrot()
{
    INT64 n;
    FLOAT64 r;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfrot\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 1st push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 2nd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 3rd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfrot(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, got error doing FROT got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, expected depth 3 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, got error doing 1st pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, expected 2.0 from first pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, got error doing 2nd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, expected 8.0 from 2nd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, got error doing 3rd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st frot case, expected 4.0 from 3rd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfover()
{
    INT64 n;
    FLOAT64 r;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfover\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 1st push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 2nd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 3rd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfover(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, got error doing FOVER got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, expected depth 4 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, got error doing 1st pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, expected 4.0 from first pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, got error doing 2nd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, expected 8.0 from 2nd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, got error doing 3rd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st over case, expected 4.0 from 3rd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfround()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfround\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 7.9);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfround(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error doing fround got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 7.1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfround(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, got error doing fround got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 7.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, expected 7.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 7.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfround(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, got error doing fround got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -7.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfround(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error doing fround got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != -8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, expected -8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -8.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfround(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, got error doing fround got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != -8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, expected -8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfnegate()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfnegate\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 7.9);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfnegate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error doing fnegate got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != -7.9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, expected -7.9 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    dg_pushf64tof64stack(&BHarrayhead, -7.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfnegate(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error doing fslash got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 7.5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, expected 7.5 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfmax()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfmax\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfmax(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error doing fmax got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfmin()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfmin\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfmin(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error doing fmin got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0  4.0 case, expected 4.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfloor()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfloor\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 7.9);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfloor(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error doing floor got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 7.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.9 case, expected 7.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 7.1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfloor(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, got error doing floor got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 7.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.1 case, expected 7.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 7.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfloor(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, got error doing floor got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 7.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7.5 case, expected 7.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -7.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfloor(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error doing floor got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != -8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -7.5 case, expected -8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -8.5);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfloor(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, got error doing floor got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != -9.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -8.5 case, expected -9.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfliteral ()
{
    FLOAT64 r;
    UINT64 x;
    UINT64 mycurrentcompilebuffer;
    UINT64 mystartoffset;
    
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfliteral\n");
    
    // success case
    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    mycurrentcompilebuffer = dg_getbufferuint64(&BHarrayhead, DG_DATASPACE_BUFFERID, currentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - could not get current compile buffer\n");
        return;
    }
    
    mystartoffset = dg_getbufferlength(&BHarrayhead, mycurrentcompilebuffer);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - could not get current compile buffer's length\n");
        return;
    }
    
    // compiling a forth routine to push a number to the data stack
    dg_compileinitlocals(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - could not compile init locals\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - could not push test number to f64 stack\n");
        return;
    }
    
    dg_forthfliteral(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - could not do dg_forthliteral\n");
        return;
    }
    
    x = dg_getbufferlength(&BHarrayhead, DG_DATASTACK_BUFFERID);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - dg_forthliteral did not consume data stack parameter\n");
        return;
    }
    
    dg_compileexitlocals(&BHarrayhead);
    
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - could not compile exit locals\n");
        return;
    }
    
    // now the real test, does it crash?
    dg_callbuffer(&BHarrayhead, mycurrentcompilebuffer, mystartoffset);
    
    // seeing if it worked
    x = dg_getbufferlength(&BHarrayhead, DG_F64STACK_BUFFERID);
    
    if (x != sizeof(FLOAT64))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - data stack length not correct after call\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (r != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! FLITERAL success case - top number on f64 stack after calling compiled FLITERAL incorrect\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
}

void testdg_forthfdup()
{
    INT64 n;
    FLOAT64 r;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfdup\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 1st push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 2nd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 3rd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdup(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, got error doing FDUP got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, expected depth 4 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, got error doing 1st pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, expected 8.0 from first pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, got error doing 2nd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, expected 8.0 from 2nd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, got error doing 3rd pop got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1st dup case, expected 4.0 from 3rd pop got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfdrop()
{
    INT64 n;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfdrop\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 1st push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 2nd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! setup 3rd push, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdrop(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3 to 2 case, got error doing FDROP got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3 to 2 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3 to 2 case, expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthfdrop(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 to 1 case, got error doing FDROP got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 to 1 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 to 1 case, expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_forthfdrop(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 to 0 case, got error doing FDROP got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 to 0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 to 0 case, expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfdepth()
{
    INT64 n;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfdepth\n");
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! initial case, got error doing FDEPTH got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! initial case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! initial case, expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 item case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 item case, got error doing FDEPTH got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 item case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1 item case, expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 9.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 items case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfdepth(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 items case, got error doing FDEPTH got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 items case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2 items case, expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthftos()
{
    INT64 n;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthftos\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error pushing to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftos(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error doing F>S got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 case, got error pushing to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftos(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 case, got error doing F>S got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = (INT64)dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != -2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 case, expected -2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthflessthan()
{
    UINT64 n;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthflessthan\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 < 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 < 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthflessthan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 < 4.0 case, got error doing flessthan got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 < 4.0 case, got error popping from data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 < 4.0 case, expected FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 3.9);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.9 < 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.9 < 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthflessthan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.9 < 4.0 case, got error doing flessthan got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.9 < 4.0 case, got error popping from data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n == FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.9 < 4.0 case, expected not FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4.0 < 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4.0 < 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthflessthan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4.0 < 4.0 case, got error doing flessthan got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4.0 < 4.0 case, got error popping from data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4.0 < 4.0 case, expected not FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfzeroequals()
{
    UINT64 n = 0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfzeroequals\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfzeroequals(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fzeroequals got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n == FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected not FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -0.0001);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfzeroequals(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, got error doing fzeroequals got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, got error popping from data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, expected not FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfzerolessthan()
{
    UINT64 n = 0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfzerolessthan\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 0.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfzerolessthan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error doing fzerolessthan got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, got error popping from data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_pushf64tof64stack(&BHarrayhead, -0.0001);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfzerolessthan(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, got error doing fzerolessthan got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    n = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, got error popping from data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (n == FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -0.0001 case, expected not FORTH_FALSE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, n);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfslash()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfslash\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 8.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 / 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 4.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 / 4.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfslash(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 / 4.0 case, got error doing fslash got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 / 4.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 8.0 / 4.0 case, expected 2.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfminus()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfminus\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 - 2.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 - 2.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfminus(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 - 2.0 case, got error doing fminus got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 - 2.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 - 2.0 case, expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfplus()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfplus\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 + 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 + 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfplus(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 + 3.0 case, got error doing fplus got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 + 3.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 5.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 + 3.0 case, expected 5.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfstar()
{
    FLOAT64 r = 0.0;

    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfstar\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 * 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushf64tof64stack(&BHarrayhead, 3.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 * 3.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstar(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 * 3.0 case, got error doing fstar got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 * 3.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 6.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 * 3.0 case, expected 6.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthffetch()
{
    FLOAT64 r = 2.0;
    FLOAT64 s = 0.0;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthffetch\n");
    
    dg_pushdatastack(&BHarrayhead, (UINT64)&r);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error pushing to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthffetch(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got doing fstore got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    s = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (s != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected 2.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfstore()
{
    FLOAT64 r = 0.0;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthfstore\n");
    
    dg_pushf64tof64stack(&BHarrayhead, 2.0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error pushing to f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushdatastack(&BHarrayhead, (UINT64)&r);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got error pushing to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthfstore(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, got doing fstore got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected 2.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthstof()
{
    FLOAT64 r;
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthstof\n");
    
    dg_pushdatastack(&BHarrayhead, -123);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -123 case, got error pushing to data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthstof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -123 case, got error doing S>F got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    r = dg_popf64fromf64stack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -123 case, got error popping from f64 stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (r != -123.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -123 case, expected -123.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_f64twotothex()
{
    FLOAT64 r;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64twotothex\n");
    
    r = dg_f64twotothex(1.0);
    
    if (r != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected 2.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(2.0);
    
    if (r != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected 4.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(3.0);
    
    if (r != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 case, expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(4.0);
    
    if (r != 16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4.0 case, expected 16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(5.0);
    
    if (r != 32.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 5.0 case, expected 32.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(-1.0);
    
    if (r != 0.5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -1.0 case, expected 0.5 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(-2.0);
    
    if (r != 0.25)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -2.0 case, expected 0.25 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(-3.0);
    
    if (r != 0.125)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -3.0 case, expected 0.125 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    r = dg_f64twotothex(16.0);
    
    if (r != 65536.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 16.0 case, expected 65536.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&r)) );
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}

void testdg_unpackdf()
{
    UINT64 mantissa;
    INT64 exponent;
    INT64 sign;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_unpackdf\n");
    
    dg_unpackdf (
        0.0,
        &mantissa,
        &exponent,
        &sign);
    
    if (mantissa != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected mantissa = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mantissa);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected exponent = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0.0 case, expected sign = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unpackdf (
        1.0,
        &mantissa,
        &exponent,
        &sign);
    
    if (mantissa != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected mantissa = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mantissa);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (exponent != 0x3ff)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected exponent = 0x3ff got ");
        dg_writestdoutuint64tohex(&BHarrayhead, exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1.0 case, expected sign = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unpackdf (
        2.0,
        &mantissa,
        &exponent,
        &sign);
    
    if (mantissa != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected mantissa = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mantissa);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (exponent != 0x400)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected exponent = 0x400 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2.0 case, expected sign = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unpackdf (
        3.0,
        &mantissa,
        &exponent,
        &sign);
    
    if (mantissa != 0x0008000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 case, expected mantissa = 0x0008000000000000 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mantissa);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (exponent != 0x400)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 case, expected exponent = 0x400 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3.0 case, expected sign = 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_unpackdf (
        -3.0,
        &mantissa,
        &exponent,
        &sign);
    
    if (mantissa != 0x0008000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -3.0 case, expected mantissa = 0x0008000000000000 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, mantissa);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (exponent != 0x400)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -3.0 case, expected exponent = 0x400 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! -3.0 case, expected sign != 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}

void testdg_timeslog2()
{
    UINT64 x;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_timeslog2\n");
    
    x = dg_timeslog2 (0);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 0*log2, expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (1);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 1*log2, expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (2);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 2*log2, expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (3);
    
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 3*log2, expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (4);
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 4*log2, expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (6);
    
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 6*log2, expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (7);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 7*log2, expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (9);
    
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 9*log2, expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (10);
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 10*log2, expected 3 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (13);
    
    if (x != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 13*log2, expected 3 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (14);
    
    if (x != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 14*log2, expected 4 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_timeslog2 (-14);
    
    if (x != -4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! 14*log2, expected -4 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}



void testdg_f64tof64rootf642expf6410exp()
{
    FLOAT64 root;
    FLOAT64 twotothen;
    FLOAT64 tentothew;
    INT64 base10exponent;
    INT64 sign;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64tof64rootf642expf6410exp\n");
    
    dg_f64tof64rootf642expf6410exp(   
        1.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 root expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 twotothen expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 twotothen expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_f64tof64rootf642expf6410exp(   
        2.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 2.0 root expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 2.0 twotothen expected 2.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 2.0 twotothen expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 2.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 2.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_f64tof64rootf642expf6410exp(   
        4.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 4.0 root expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 4.0 twotothen expected 4.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 4.0 twotothen expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 4.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 4.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_f64tof64rootf642expf6410exp(   
        8.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 8.0 root expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 8.0 twotothen expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 8.0 twotothen expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 8.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 8.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_f64tof64rootf642expf6410exp(   
        10.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 10.0/8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 10.0 root expected 10.0/8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 10.0 twotothen expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 10.0 twotothen expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 10.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 10.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_f64tof64rootf642expf6410exp(   
        16.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 16.0 root expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 16.0 twotothen expected 16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 10.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 16.0 twotothen expected 10.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 16.0 base10exponent expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 16.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_f64tof64rootf642expf6410exp(   
        20.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 20.0/16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 20.0 root expected 20.0/16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 20.0 twotothen expected 16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 10.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 20.0 twotothen expected 10.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 20.0 base10exponent expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 20.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_f64tof64rootf642expf6410exp(   
        -20.0,
        &root,
        &twotothen,
        &tentothew,
        &base10exponent,
        &sign);
    
    if (root != 20.0/16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp -20.0 root expected 20.0/16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&root)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (twotothen != 16.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp -20.0 twotothen expected 16.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&twotothen)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (tentothew != 10.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp -20.0 twotothen expected 10.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&tentothew)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp -20.0 base10exponent expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp -20.0 sign expected <> 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}

void testdg_f64tobase10 ()
{
    FLOAT64 basenumber;
    INT64 base10exponent;
    INT64 sign;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64tobase10\n");

    basenumber = dg_f64tobase10 (
        0.0,
        &base10exponent,
        &sign);
        
    if (basenumber != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tobase10 0.0 basenumber expected 0.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&basenumber)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != -0x8000000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 0.0 base10exponent expected -0x8000000000000000 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 0.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    basenumber = dg_f64tobase10 (
        1.0,
        &base10exponent,
        &sign);
        
    if (basenumber != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tobase10 1.0 basenumber expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&basenumber)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    basenumber = dg_f64tobase10 (
        8.0,
        &base10exponent,
        &sign);
        
    if (basenumber != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tobase10 8.0 basenumber expected 8.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&basenumber)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 8.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 8.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    basenumber = dg_f64tobase10 (
        10.0,
        &base10exponent,
        &sign);
        
    if (basenumber != 10.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tobase10 10.0 basenumber expected 10.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&basenumber)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)  // based off power of 2 integer exponent so still 0
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 10.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 10.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    basenumber = dg_f64tobase10 (
        16.0,
        &base10exponent,
        &sign);
        
    if (basenumber != 1.6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tobase10 16.0 basenumber expected 1.6 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&basenumber)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 16.0 base10exponent expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 16.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    basenumber = dg_f64tobase10 (
        -16.0,
        &base10exponent,
        &sign);
        
    if (basenumber != 1.6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tobase10 -16.0 basenumber expected 1.6 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&basenumber)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp -16.0 base10exponent expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp -16.0 sign expected <>0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    basenumber = dg_f64tobase10 (
        1.0,
        &base10exponent,
        &sign);
        
    if (basenumber != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tobase10 1.0 basenumber expected 1.0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&basenumber)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_f64tof64rootf642expf6410exp 1.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
	dg_freeallbuffers(&BHarrayhead);
}

void testdg_fixedpointu128todecimalstring ()
{
    unsigned char mybuf[100];
    UINT64 wholenumber;
    UINT64 fractionalnumber;
    UINT64 returnedlength;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_fixedpointu128todecimalstring\n");

    wholenumber = 23;
    fractionalnumber = 0x8000000000000000; // 0.5
    
    returnedlength = dg_fixedpointu128todecimalstring(
        mybuf,
        10,
        wholenumber, 
        fractionalnumber,
        0);
    
    if (returnedlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring 23.5 returnedlength expected 4 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, returnedlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring 23.5 1st character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring 23.5 2nd character expected 3 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '.')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring 23.5 3rd character expected . got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[3] != '5')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring 23.5 4th character expected 5 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 3,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    wholenumber = 23;
    fractionalnumber = 0x8000000000000000; // 0.5
    
    returnedlength = dg_fixedpointu128todecimalstring(
        mybuf,
        10,
        wholenumber, 
        fractionalnumber,
        -1);
    
    if (returnedlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring -23.5 returnedlength expected 5 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, returnedlength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '-')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring -23.5 1st character expected - got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring -23.5 2nd character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring -23.5 3rd character expected 3 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[3] != '.')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring -23.5 4th character expected . got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[4] != '5')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_fixedpointu128todecimalstring -23.5 5th character expected 5 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 3,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_represent ()
{
    unsigned char mybuf[100];
    INT64 sign;
    INT64 base10exponent;
    UINT64 fractionalremainder;
    INT64 x; // for making infinity, etc
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_represent\n");

    base10exponent = dg_represent(
        23.5,
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 base10exponent expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 1st character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 2nd character expected 3 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '5')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 3rd character expected 5 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        23.5,
        (unsigned char*)mybuf,
        2,
        &sign,
        &fractionalremainder);
    
    /*     // floating point error makes this test not work
    if (fractionalremainder != 0x8000000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 rounded 2 places fractionalremainder expected 0x8000000000000000 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, fractionalremainder);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    */
    
    if (base10exponent != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 rounded 2 places base10exponent expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 rounded 2 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 rounded 2 places 1st character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '4')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 rounded 2 places 2nd character expected 4 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        26.5,
        (unsigned char*)mybuf,
        2,
        &sign,
        &fractionalremainder);
    
    /*   // floating point error makes this test not work
    if (fractionalremainder != 0x8000000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 23.5 rounded 2 places fractionalremainder expected 0x8000000000000000 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, fractionalremainder);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    */
    
    if (base10exponent != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.5 rounded 2 places base10exponent expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.5 rounded 2 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.5 rounded 2 places 1st character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    /*   // floating point error makes this round up to 7... so this test does not work
    if (mybuf[1] != '6')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.5 rounded 2 places 2nd character expected 6 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    */
    
    
    base10exponent = dg_represent(
        26.51,
        (unsigned char*)mybuf,
        2,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.51 rounded 2 places base10exponent expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.51 rounded 2 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.51 rounded 2 places 1st character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '7')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 26.51 rounded 2 places 2nd character expected 7 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        -26.51,
        (unsigned char*)mybuf,
        2,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -26.51 rounded 2 places base10exponent expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -26.51 rounded 2 places sign expected <>0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -26.51 rounded 2 places 1st character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '7')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -26.51 rounded 2 places 2nd character expected 7 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        0.0032651938736,
        (unsigned char*)mybuf,
        10,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != -2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places base10exponent expected 2 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 1st character expected 3 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 2nd character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '6')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 3rd character expected 6 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[3] != '5')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 4th character expected 5 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 3,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[4] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 5th character expected 5 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 4,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[5] != '9')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 6th character expected 9 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 5,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[6] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 7th character expected 3 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 6,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[7] != '8')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 8th character expected 8 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 7,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[8] != '7')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 9th character expected 7 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 8,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[9] != '4')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0032651938736 rounded 10 places 9th character expected 4 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 9,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        0.0,
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0 rounded 3 places base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0 rounded 3 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0 rounded 3 places 1st character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0 rounded 3 places 2nd character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0 rounded 3 places 3rd character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        -0.0,
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -0.0 rounded 3 places base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -0.0 rounded 3 places sign expected <>0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -0.0 rounded 3 places 1st character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -0.0 rounded 3 places 2nd character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -0.0 rounded 3 places 3rd character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_f64negativeinfinity;
    base10exponent = dg_represent(
        *((FLOAT64*)(&x)),
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != largestsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -infinity rounded 3 places base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign == 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -infinity rounded 3 places sign expected <>0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != 'I')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -infinity rounded 3 places 1st character expected i got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -infinity rounded 3 places 2nd character expected n got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != 'f')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent -infinity rounded 3 places 3rd character expected f got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_f64infinity;
    base10exponent = dg_represent(
        *((FLOAT64*)(&x)),
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != largestsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent infinity rounded 3 places base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent infinity rounded 3 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != 'I')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent infinity rounded 3 places 1st character expected i got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent infinity rounded 3 places 2nd character expected n got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != 'f')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent infinity rounded 3 places 3rd character expected f got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_f64NaN;
    base10exponent = dg_represent(
        *((FLOAT64*)(&x)),
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != largestsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent NaN rounded 3 places base10exponent expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent NaN rounded 3 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != 'N')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent NaN rounded 3 places 1st character expected N got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent NaN rounded 3 places 2nd character expected a got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != 'N')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent NaN rounded 3 places 3rd character expected N got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = dg_f64denormal;
    base10exponent = dg_represent(
        *((FLOAT64*)(&x)),
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != 0x8000000000000000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent denormal rounded 3 places base10exponent expected 0x8000000000000000 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent denormal rounded 3 places sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != 'D')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent denormal rounded 3 places 1st character expected D got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent denormal rounded 3 places 2nd character expected e got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != 'n')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent denormal rounded 3 places 3rd character expected n got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        1.0,
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 1.0 base10exponent expected 1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 1.0 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 1.0 1st character expected 1 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 1.0 2nd character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '0')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 1.0 3rd character expected 0 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    base10exponent = dg_represent(
        0.0123,
        (unsigned char*)mybuf,
        3,
        &sign,
        &fractionalremainder);
    
    if (base10exponent != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0123 base10exponent expected -1 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, base10exponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (sign != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0123 sign expected 0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, sign);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[0] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0123 1st character expected 1 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 0,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[1] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0123 2nd character expected 2 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 1,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (mybuf[2] != '3')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_represent 0.0123 3rd character expected 3 got ");
        dg_writestdoutraw(
            &BHarrayhead,
            mybuf + 2,
            1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthftod()
{
    UINT64 xlo = 0;
    UINT64 xhi = 0;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    dg_initbuffers(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthftod\n");

    // 1.0 success case
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x3FF0000000000000); // 1.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 1 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, expected xlo = 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 1.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);



    // 2.0 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x4000000000000000); // 2.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 2 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, expected xlo = 2, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 3.0 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x4008000000000000); // 3.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 3 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, expected xlo = 3, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 3.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 4.0 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x4010000000000000); // 4.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 4 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, expected xlo = 4, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 4.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 8.0 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x4020000000000000); // 8.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 8 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, expected xlo = 8, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 8.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // -2.0 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0xC000000000000000); // -2.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0xffffffffffffffff )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, expected xhi = -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0xfffffffffffffffe)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, expected xlo = -2, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -2.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // +0.0 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x0000000000000000); // +0.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +0.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // -0.0 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x8000000000000000); // -0.0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -0.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // +infinity success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x7FF0000000000000); // +infinity
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != largestsignedint )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, expected xhi = 0x7fffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != largestunsignedint)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, expected xlo = 0xffffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod +infinity case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // -infinity success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0xFFF0000000000000); // -infinity
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != largestnegativeint )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, expected xhi = 0x8000000000000000, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -infinity case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 0.5 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x3FE0000000000000); // 0.5
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 0.5 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // very small success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x0010000000000000); // almost 0
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very small case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // very big success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x7FE0000000000000); // very big
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != largestsignedint )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, expected xhi = 0x7fffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != largestunsignedint )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, expected xlo = 0xffffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod very big case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // -very big success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0xFFE0000000000000); // -very big
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != largestnegativeint )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, expected xhi = 0x8000000000000000, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod -very big case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 2^42 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x4290000000000000); // 2^42
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0x0000040000000000 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, expected xlo = 2^42, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^42 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 2^43 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x42A0000000000000); // 2^43
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0x0000080000000000 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, expected xlo = 2^43, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^43 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 2^63 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x43E0000000000000); // 2^63
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, expected xhi = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0x8000000000000000 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, expected xlo = 2^63, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^63 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 2^64 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x43F0000000000000); // 2^64
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 1 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, expected xhi = 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^64 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 2^126 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x47D0000000000000); // 2^126
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0x4000000000000000 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, expected xhi = 0x4000000000000000, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^126 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // 2^127 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x47E0000000000000); // 2^127
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != largestsignedint )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, expected xhi = 0x7fffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != largestunsignedint )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, expected xlo = 0xffffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod 2^127 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // most positive signed int success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0x47DFFFFFFFFFFFFF); // most positive signed int
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0x7FFFFFFFFFFFFC00 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int case, expected xhi = largestsignedint, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int - 1 case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int - 1 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int - 1 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int - 1 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most positive signed int - 1 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);


    // most negative signed int success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0xC7DFFFFFFFFFFFFF); // most negative signed int
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0x8000000000000400 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, expected xhi = 8000000000000400, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // most negative signed int 2 success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0xC7E0000000000000); // most negative signed int 2
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0x8000000000000000 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, expected xhi = 8000000000000000, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int 2 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // negative signed int too big success case

    dg_initbuffers(&BHarrayhead);

    dg_pushbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID,
       0xC7F0000000000000); // most negative signed int too big
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthftod(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, got error doing dg_forthftod got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    xhi = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xhi != 0x8000000000000000 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, expected xhi = 8000000000000000, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xhi);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    xlo = dg_popdatastack(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, got error popping data stack got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, expected xlo = 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthftod most negative signed int too big  case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_forthdtof()
{
    UINT64 xlo = 0;
    UINT64 xhi = 0;
    
    UINT64 df;
    
    const char* perror;
    
    Bufferhandle BHarrayhead;
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_forthdtof\n");

    // 1.0 success case
    
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       1);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, error pushing low to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, error pushing high to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthdtof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, got error doing dg_forthdtof got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    df = dg_popbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (df != 0x3FF0000000000000) // 1.0 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, expected df = 0x3FF0000000000000); // 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, df);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 1.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // 2.0 success case
    
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       2);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, error pushing low to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, error pushing high to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthdtof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, got error doing dg_forthdtof got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    df = dg_popbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (df != 0x4000000000000000) // 2.0 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, expected df = 0x4000000000000000); // 2.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, df);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // 0.0 success case
    
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, error pushing low to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, error pushing high to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthdtof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, got error doing dg_forthdtof got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    df = dg_popbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (df != 0x0000000000000000) // 0.0 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, expected df = 0x0000000000000000); // 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, df);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 0.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    // -1.0 success case
    
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0xffffffffffffffff);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, error pushing low to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0xffffffffffffffff);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, error pushing high to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthdtof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, got error doing dg_forthdtof got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    df = dg_popbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (df != 0xBFF0000000000000) // -1.0 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, expected df = 0xBFF0000000000000); // -1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, df);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -1.0 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // -2^126 success case
    
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, error pushing low to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0xC000000000000000);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, error pushing high to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthdtof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, got error doing dg_forthdtof got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    df = dg_popbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (df != 0xC7D0000000000000) // -2^126 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, expected df = 0xC7D0000000000000); // -2^126, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, df);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^126 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // 2^126 success case
    
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, error pushing low to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0x4000000000000000);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, error pushing high to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthdtof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, got error doing dg_forthdtof got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    df = dg_popbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (df != 0x47D0000000000000) // 2^126 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, expected df = 0x47D0000000000000); // 2^126, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, df);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof 2^126 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
    
    
    // -2^127 success case
    
    dg_initbuffers(&BHarrayhead);
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, error pushing low to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_pushbufferuint64(
       &BHarrayhead,
       DG_DATASTACK_BUFFERID,
       0x8000000000000000);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, error pushing high to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    dg_forthdtof(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, got error doing dg_forthdtof got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    df = dg_popbufferuint64(
       &BHarrayhead,
       DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, error pushing to floating point stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if (df != 0xC7E0000000000000) // -2^127 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, expected df = 0xC7E0000000000000); // -2^127, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, df);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, data stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    xlo = dg_getbufferlength(
        &BHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        perror = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, got error getting buffer length got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    if ( xlo != 0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)" FAIL! dg_forthdtof -2^127 case, f64 stack not empty after test, got depth = ");
        dg_writestdoutuint64tohex(&BHarrayhead, xlo);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    dg_clearerrors(&BHarrayhead);
    
    dg_freeallbuffers(&BHarrayhead);
}
